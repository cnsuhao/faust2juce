#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import string
import shutil
import sys
import fileinput

def processXcodeProj(path, desc):
   print "Process XCode proj"
   f = open(path, "r")
   lines = f.readlines()
   f.close()
   
   f = open(path, "w")
   for line in lines:
      line = line.replace("JuceDemoPlugin",desc["PlugName"])
      f.write(line)
   f.close()

def processPlist(path):
   # TODO: use plistlib
   print "Process PList"
   f = open(path, "r")
   lines = f.readlines()
   f.close()
   
   f = open(path, "w")
   for line in lines:
      line = line.replace("com.rawmaterialsoftware","org.grame")
      f.write(line)
   f.close()

def getText(nodelist):
   rc = ""
   for node in nodelist:
      if node.nodeType == node.TEXT_NODE:
         rc = rc + node.data
   rc = rc.lstrip('" ')
   rc = rc.rstrip('" ')
   return rc

def makeFourCharCode(value):
   r = "'"
   count = 0

   r = ""
   for c in value:
      if not r.count(c):
         r = r+c
         
   vowels = "aeiouy"
   i = 0
   while len(r)>4 and i<len(vowels):
      r = r.replace(vowels[i:i+1],"")
      i = i+1

   r = r[0:4]
   
   return "'%s'" % r

def strip(name):
   for c in u" -_:><=!()[]{};,/?+*%^¨&'$":
      name = name.replace(c,"")
   return name

def processXmlDesc(path):
   from xml.dom.minidom import parse
   dom = parse(path)
   r = {}
   faust = dom.getElementsByTagName("faust")[0]
   plugName = getText(faust.getElementsByTagName("name")[0].childNodes)
   r["PlugName"] = strip(plugName)
   r["Author"] = getText(faust.getElementsByTagName("author")[0].childNodes)
   r["Copyright"] = getText(faust.getElementsByTagName("copyright")[0].childNodes)
   r["License"] = getText(faust.getElementsByTagName("license")[0].childNodes)
   r["version"] = getText(faust.getElementsByTagName("version")[0].childNodes)
   r["NumInputs"] = getText(faust.getElementsByTagName("inputs")[0].childNodes)
   r["NumOutputs"] = getText(faust.getElementsByTagName("outputs")[0].childNodes)
   r["AuthorCode"] = makeFourCharCode(r["Author"])
   r["PluginCode"] = makeFourCharCode(r["PlugName"])
   return r

def processJucePlugDesc(path, desc):
   print "Process Juce Plugin Description"
   f = open(path, "r")
   lines = f.readlines()
   f.close()
   
   f = open(path, "w")
   for line in lines:
      for item in desc.items():
         key = "<<" + item[0] + ">>"
         val = item[1]
         line = line.replace(key,val)
      f.write(line)
   f.close()

def faust2juce(scriptDir, file):
   projectPath = os.path.join(scriptDir, "Faust2Juce")
   prefix,ext = os.path.splitext(file)
   filename = os.path.basename(prefix)
   destPath = prefix + "-juce"
   
   # duplicate project
   print "Create project:"
   print destPath
   shutil.rmtree(destPath, ignore_errors=True)
   shutil.copytree(projectPath,destPath)

   # call faust
   print "Call faust:"
   arch = os.path.join(projectPath, "FaustJuceTemplate.cpp")
   outputFile = os.path.join(destPath,"demo/src/FaustJuce.cpp")
   cmd = "faust -xml -a " + arch + " -o " + outputFile + " "+ file
   print cmd
   os.system(cmd)

   # parse XML file
   xmlDesc = file+".xml"
   desc = processXmlDesc(xmlDesc)   

   # replace xcode project
   xcodeDir = destPath+"/demo/build/mac"
   xcodeproj = xcodeDir + "/JuceDemoPlugin.xcodeproj/project.pbxproj"
   processXcodeProj(xcodeproj, desc)
   
   plist = destPath+"/demo/build/mac/Info.plist"
   processPlist(plist)
   
   jucePlugDesc = destPath+"/demo/src/JucePluginCharacteristics.h"
   processJucePlugDesc(jucePlugDesc, desc)

   # build plug
   oldcwd = os.getcwd()
   os.chdir(xcodeDir)
   os.system("xcodebuild -configuration Release")
   os.chdir(oldcwd)

if __name__ == "__main__":
   if len(sys.argv)==2:
      root = os.path.abspath(sys.argv[0])
      file = os.path.abspath(sys.argv[1])
      scriptDir = os.path.dirname(root)
      faust2juce(scriptDir, file)
   else:
      print "error"
