/*
 ==============================================================================
 
 This file is part of the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2004-9 by Raw Material Software Ltd.
 
 ------------------------------------------------------------------------------
 
 JUCE can be redistributed and/or modified under the terms of the GNU General
 Public License (Version 2), as published by the Free Software Foundation.
 A copy of the license is included in the JUCE distribution, or can be found
 online at www.gnu.org/licenses.
 
 JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 To release a closed-source product which uses JUCE, commercial licenses are
 available: visit www.rawmaterialsoftware.com/juce for more information.
 
 ==============================================================================
 */

#include "juce_amalgamated.h"
#include "FaustJuce.h"

#include <vector> 

class FaustUI : public UI
{
public:
	FaustUI()
	{
	}
	
	~FaustUI()
	{
	}	
	
	size_t getNumParameters() const
	{ 
		return mParameters.size(); 
	}
	
	float getNormalizedParameter(size_t index) const 
	{ 
		return mParameters[index].getNormalized(); 
	}
	
	void setNormalizedParameter(size_t index, float value)
	{ 
		mParameters[index].setNormalized(value);
	}
	
	const String& getParameterName(size_t index) const
	{
		return mParameters[index].name;
	}
	
	String getParameterText(size_t index) const
	{
		return String(*mParameters[index].value, 0);
	}
	
protected:
  virtual void addButton(char* label, float* zone)
	{
		mParameters.push_back(Parameter(kButton, label, zone));
	}
	
  virtual void addToggleButton(char* label, float* zone)
	{
		mParameters.push_back(Parameter(kToggleButton, label, zone));
	}
	
  virtual void addCheckButton(char* label, float* zone)
	{
		mParameters.push_back(Parameter(kCheckButton, label, zone));
	}
	
  virtual void addVerticalSlider(char* label, float* zone, float init, float min, float max, float step)
	{
		Parameter p(kVSlider, label, zone);
		p.min = min;
		p.max = max;
		p.step = step;
		p.def = init;
		mParameters.push_back(p);
	}
	
  virtual void addHorizontalSlider(char* label, float* zone, float init, float min, float max, float step)
	{
		Parameter p(kHSlider, label, zone);
		p.min = min;
		p.max = max;
		p.step = step;
		p.def = init;
		mParameters.push_back(p);
	}
	
  virtual void addNumEntry(char* label, float* zone, float init, float min, float max, float step)
	{
		Parameter p(kNumEntry, label, zone);
		p.min = min;
		p.max = max;
		p.step = step;
		p.def = init;
		mParameters.push_back(p);
	}
	
  virtual void addNumDisplay(char* label, float* zone, int precision)
	{
		Parameter p(kNumDisplay, label, zone);
		p.precision = precision;
		mParameters.push_back(p);
	}
	
  virtual void addTextDisplay(char* label, float* zone, char* names[], float min, float max) 
	{
		Parameter p(kNumEntry, label, zone);
		p.min = min;
		p.max = max;
		
		for(int i=0; names[i] != NULL; ++i)
			p.names.push_back(String(names[i]));
		
		mParameters.push_back(p);
	}
	
  virtual void addHorizontalBargraph(char* label, float* zone, float min, float max)
	{
		Parameter p(kHBarGraph, label, zone);
		p.min = min;
		p.max = max;
		mParameters.push_back(p);
	}
	
  virtual void addVerticalBargraph(char* label, float* zone, float min, float max)
	{
		Parameter p(kVBarGraph, label, zone);
		p.min = min;
		p.max = max;
		mParameters.push_back(p);
	}
	
  virtual void openFrameBox(char* label)
	{
	}
	
  virtual void openTabBox(char* label) 
	{
	}
	
  virtual void openHorizontalBox(char* label)
	{
	}
	
  virtual void openVerticalBox(char* label)
	{
	}
	
  virtual void closeBox()
	{
	}
	
  virtual void run() 
	{
	}
	
private:
	enum ControllerType
	{
		kButton = 0, kToggleButton, kCheckButton, kVSlider, kHSlider, kNumEntry, 
		kNumDisplay, kTextDisplay, kHBarGraph, kVBarGraph
	};
	
	struct Parameter 
	{
		ControllerType type;
		String name;
		float *value;
		float def,min,max,step;
		int precision;
		std::vector<String> names;
		
		Parameter(ControllerType type_, const String &name_, float *value_)
		: name(name_), value(value_), def(*value_), min(0), max(1), step(0)
		{
		}
		
		float getNormalized() const
		{
			return (*value - min) / (max-min);
		}
		
		void setNormalized(float v)
		{
			*value = min + (max-min)*v;
		}		
	};
	std::vector<Parameter> mParameters;
};

//==============================================================================

class DemoJuceFilter;

//==============================================================================
class DemoEditorComponent : public AudioProcessorEditor, public ChangeListener, public SliderListener
{
public:
	DemoEditorComponent (DemoJuceFilter* const ownerFilter);
	~DemoEditorComponent();
	
	void changeListenerCallback (void* source);	
	void sliderValueChanged (Slider*);
	
	void paint (Graphics& g);
	void resized();
	
private:
	void updateParametersFromFilter();
	DemoJuceFilter* getFilter() const throw()       { return (DemoJuceFilter*) getAudioProcessor(); }
	
private:
	TooltipWindow tooltipWindow;	
};

class DemoJuceFilter : public AudioProcessor, public ChangeBroadcaster
{
public:
	DemoJuceFilter();
	~DemoJuceFilter();
	
	void prepareToPlay (double sampleRate, int samplesPerBlock);
	void releaseResources();
	
	void processBlock (AudioSampleBuffer& buffer,
										 MidiBuffer& midiMessages);
	
	//==============================================================================
	AudioProcessorEditor* createEditor();
	
	//==============================================================================
	const String getName() const;
	
	int getNumParameters();
	
	float getParameter (int index);
	void setParameter (int index, float newValue);
	
	const String getParameterName (int index);
	const String getParameterText (int index);
	
	const String getInputChannelName (const int channelIndex) const;
	const String getOutputChannelName (const int channelIndex) const;
	bool isInputChannelStereoPair (int index) const;
	bool isOutputChannelStereoPair (int index) const;
	
	bool acceptsMidi() const;
	bool producesMidi() const;
	
	//==============================================================================
	int getNumPrograms()                                        { return 0; }
	int getCurrentProgram()                                     { return 0; }
	void setCurrentProgram (int index)                          { }
	const String getProgramName (int index)                     { return String::empty; }
	void changeProgramName (int index, const String& newName)   { }
	
	//==============================================================================
	void getStateInformation (MemoryBlock& destData);
	void setStateInformation (const void* data, int sizeInBytes);
	
	juce_UseDebuggingNewOperator
	
private:
	dsp *mpDSP;
	FaustUI *mpUI;
};

//==============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new DemoJuceFilter();
}

//==============================================================================
DemoJuceFilter::DemoJuceFilter()
: mpDSP(NULL)
, mpUI(NULL)
{
	mpUI = new FaustUI();
	mpDSP = faustCreateDSP();
	mpDSP->buildUserInterface(mpUI);
}

DemoJuceFilter::~DemoJuceFilter()
{
	delete mpDSP;
	delete mpUI;
}

//==============================================================================
const String DemoJuceFilter::getName() const
{
	return "Faust";
}

int DemoJuceFilter::getNumParameters()
{
	return mpUI->getNumParameters();
}

float DemoJuceFilter::getParameter (int index)
{
	if(index>=0 && index<getNumParameters())
	{
		return mpUI->getNormalizedParameter(index);
	}
	return 0.f;
}

void DemoJuceFilter::setParameter (int index, float newValue)
{
	if(index>=0 && index<getNumParameters())
	{
		mpUI->setNormalizedParameter(index, newValue);
		sendChangeMessage (this);
	}
}

const String DemoJuceFilter::getParameterName (int index)
{
	if(index>=0 && index<getNumParameters())
	{
		return mpUI->getParameterName(index);
	}
	return String::empty;
}

const String DemoJuceFilter::getParameterText (int index)
{
	if(index>=0 && index<getNumParameters())
	{
		return mpUI->getParameterText(index);
	}
	return String::empty;
}

const String DemoJuceFilter::getInputChannelName (const int channelIndex) const
{
	return String (channelIndex + 1);
}

const String DemoJuceFilter::getOutputChannelName (const int channelIndex) const
{
	return String (channelIndex + 1);
}

bool DemoJuceFilter::isInputChannelStereoPair (int index) const
{
	return true;
}

bool DemoJuceFilter::isOutputChannelStereoPair (int index) const
{
	return true;
}

bool DemoJuceFilter::acceptsMidi() const
{
	return true;
}

bool DemoJuceFilter::producesMidi() const
{
	return true;
}

//==============================================================================
void DemoJuceFilter::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	if(mpDSP)
	{
		mpDSP->init(sampleRate);
	}
}

void DemoJuceFilter::releaseResources()
{
}

void DemoJuceFilter::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{	
	assert(mpDSP->getNumInputs()<= buffer.getNumChannels());
	assert(mpDSP->getNumOutputs()<= buffer.getNumChannels());
	if(mpDSP	&& mpDSP->getNumInputs()<= buffer.getNumChannels() 
						&& mpDSP->getNumOutputs() <= buffer.getNumChannels() )
	{
		mpDSP->compute(buffer.getNumSamples(), 
									 buffer.getArrayOfChannels(), 
									 buffer.getArrayOfChannels());
	}
	
	// in case we have more outputs than inputs, we'll clear any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
	{
		buffer.clear (i, 0, buffer.getNumSamples());
	}
}

//==============================================================================
AudioProcessorEditor* DemoJuceFilter::createEditor()
{
	return new GenericAudioProcessorEditor(this);
	//return new DemoEditorComponent (this);
}

//==============================================================================
void DemoJuceFilter::getStateInformation (MemoryBlock& destData)
{
	XmlElement xmlState (T("faust"));
	xmlState.setAttribute (T("pluginVersion"), 1);
	xmlState.setAttribute (T("pluginName"), getName());
	copyXmlToBinary (xmlState, destData);
}

void DemoJuceFilter::setStateInformation (const void* data, int sizeInBytes)
{ 
	XmlElement* const xmlState = getXmlFromBinary (data, sizeInBytes);
	if (xmlState != 0)
	{
		// check that it's the right type of xml..
		if (xmlState->hasTagName (T("faust")))
		{
			sendChangeMessage (this);
		}		
		delete xmlState;
	}
}

//==============================================================================
DemoEditorComponent::DemoEditorComponent (DemoJuceFilter* const ownerFilter)
: AudioProcessorEditor (ownerFilter)
{			
	setSize (600,400);
	ownerFilter->addChangeListener (this);
}

DemoEditorComponent::~DemoEditorComponent()
{
	getFilter()->removeChangeListener (this);
	
	deleteAllChildren();
}

//==============================================================================
void DemoEditorComponent::paint (Graphics& g)
{
	// just clear the window
	g.fillAll (Colour::greyLevel (0.9f));
}

void DemoEditorComponent::resized()
{
}

//==============================================================================
void DemoEditorComponent::changeListenerCallback (void* source)
{
	// this is the filter telling us that it's changed, so we'll update our
	// display of the time, midi message, etc.
	updateParametersFromFilter();
}

void DemoEditorComponent::sliderValueChanged (Slider*)
{
	//getFilter()->setParameterNotifyingHost (0, (float) gainSlider->getValue());
}

//==============================================================================
void DemoEditorComponent::updateParametersFromFilter()
{
	/*
	 DemoJuceFilter* const filter = getFilter();	
	 filter->getCallbackLock().enter();	
	 const float newGain = filter->getParameter (0);	
	 filter->getCallbackLock().exit();
	 
	 gainSlider->setValue (newGain, false);
	 */
}
