#ifndef SAVEGAME_H
#define SAVEGAME_H

class FDataStreamBase;
enum SavegameVariableTypes;

#include "JustInTimeArray.h"
#include "BoolArray.h"

// enum values for each class used in the savegame.
// ideally each class using SavegameVariableTypes should have an index here.
// Extending to the end is savegame safe. Altering the existing layout isn't.
enum SavegameClassTypes
{
	SAVEGAME_CLASS_AREA,
	SAVEGAME_CLASS_MAP,
	SAVEGAME_CLASS_PLOT,
	SAVEGAME_CLASS_UNIT,
	SAVEGAME_CLASS_UNIT_AI,

	NUM_SAVEGAME_CLASS_TYPES,

	FIRST_SAVEGAME_CLASS_TYPES = 0,
};

class CvSavegameReaderBase;
class CvSavegameWriterBase;

class CvSavegameReader
{
public:
	CvSavegameReader(CvSavegameReaderBase& readerBase);
	CvSavegameReader(const CvSavegameReader& reader);

	void AssignClassType(SavegameClassTypes eType);

	void Read(SavegameVariableTypes& variable);

	void Read(int& variable);
	void Read(short& variable);
	void Read(char& variable);

	void Read(unsigned int& variable);
	void Read(unsigned short& variable);
	void Read(byte& variable);

	void Read(bool& variable);
	
	void Read(CvString& szString);
	void Read(CvWString& szString);
	
	template<class T>
	void Read(JustInTimeArray<T>& jitArray);

	void Read(BoolArray& baArray);
	void Read(PlayerBoolArray& array); 
	void Read(IDInfo& idInfo);

	// workaround because we can't use references on bitfields
	template<typename T>
	T ReadBitfield(T variable);

	// Add all enums used in savegames
	void Read(CardinalDirectionTypes& variable) { Read((int&)variable); }
	void Read(CalendarTypes         & variable) { Read((int&)variable); }
	void Read(CustomMapOptionTypes  & variable) { Read((int&)variable); }
	void Read(DirectionTypes        & variable) { Read((int&)variable); }
	void Read(GameType              & variable) { Read((int&)variable); }
	void Read(PlayerTypes           & variable) { Read((int&)variable); }
	void Read(PlotTypes             & variable) { Read((int&)variable); }
	void Read(SlotClaim             & variable) { Read((int&)variable); }
	void Read(SlotStatus            & variable) { Read((int&)variable); }
	void Read(TeamTypes             & variable) { Read((int&)variable); }
	void Read(TurnTimerTypes        & variable) { Read((int&)variable); }
	
	// everything linked to xml file enums
	void Read(ArtStyleTypes         & variable) { ReadXmlEnum(variable); }
	void Read(BonusTypes            & variable) { ReadXmlEnum(variable); }
	void Read(BuildTypes            & variable) { ReadXmlEnum(variable); }
	void Read(BuildingTypes         & variable) { ReadXmlEnum(variable); }
	void Read(BuildingClassTypes    & variable) { ReadXmlEnum(variable); }
	void Read(SpecialBuildingTypes  & variable) { ReadXmlEnum(variable); }
	void Read(CivEffectTypes        & variable) { ReadXmlEnum(variable); }
	void Read(CivicTypes            & variable) { ReadXmlEnum(variable); }
	void Read(CivicOptionTypes      & variable) { ReadXmlEnum(variable); }
	void Read(CivilizationTypes     & variable) { ReadXmlEnum(variable); }
	void Read(ClimateTypes          & variable) { ReadXmlEnum(variable); }
	void Read(ColorTypes            & variable) { ReadXmlEnum(variable); }
	void Read(CultureLevelTypes     & variable) { ReadXmlEnum(variable); }
	void Read(DiplomacyTypes        & variable) { ReadXmlEnum(variable); }
	void Read(EmphasizeTypes        & variable) { ReadXmlEnum(variable); }
	void Read(EraTypes              & variable) { ReadXmlEnum(variable); }
	void Read(EuropeTypes           & variable) { ReadXmlEnum(variable); }
	void Read(EventTypes            & variable) { ReadXmlEnum(variable); }
	void Read(EventTriggerTypes     & variable) { ReadXmlEnum(variable); }
	void Read(FatherTypes           & variable) { ReadXmlEnum(variable); }
	void Read(FatherPointTypes      & variable) { ReadXmlEnum(variable); }
	void Read(FeatureTypes          & variable) { ReadXmlEnum(variable); }
	void Read(GameOptionTypes       & variable) { ReadXmlEnum(variable); }
	void Read(GameSpeedTypes        & variable) { ReadXmlEnum(variable); }
	void Read(GoodyTypes            & variable) { ReadXmlEnum(variable); }
	void Read(HandicapTypes         & variable) { ReadXmlEnum(variable); }
	void Read(HurryTypes            & variable) { ReadXmlEnum(variable); }
	void Read(ImprovementTypes      & variable) { ReadXmlEnum(variable); }
	void Read(LeaderHeadTypes       & variable) { ReadXmlEnum(variable); }
	void Read(MemoryTypes           & variable) { ReadXmlEnum(variable); }
	void Read(PlayerColorTypes      & variable) { ReadXmlEnum(variable); }
	void Read(PlayerOptionTypes     & variable) { ReadXmlEnum(variable); }
	void Read(ProfessionTypes       & variable) { ReadXmlEnum(variable); }
	void Read(PromotionTypes        & variable) { ReadXmlEnum(variable); }
	void Read(RouteTypes            & variable) { ReadXmlEnum(variable); }
	void Read(SeaLevelTypes         & variable) { ReadXmlEnum(variable); }
	void Read(TerrainTypes          & variable) { ReadXmlEnum(variable); }
	void Read(TraitTypes            & variable) { ReadXmlEnum(variable); }
	void Read(UnitTypes             & variable) { ReadXmlEnum(variable); }
	void Read(UnitAITypes           & variable) { ReadXmlEnum(variable); }
	void Read(UnitClassTypes        & variable) { ReadXmlEnum(variable); }
	void Read(UnitCombatTypes       & variable) { ReadXmlEnum(variable); }
	void Read(SpecialUnitTypes      & variable) { ReadXmlEnum(variable); }
	void Read(VictoryTypes          & variable) { ReadXmlEnum(variable); }
	void Read(YieldTypes            & variable) { ReadXmlEnum(variable); }
	void Read(WorldSizeTypes        & variable) { ReadXmlEnum(variable); }

	void ReadConversionTable();

	int ConvertIndex(JITarrayTypes eType, int iIndex) const;

#ifndef MakefileCompilation
	// remove IntelliSense errors, which causes bogus red lines in the code
	// This isn't compiled and won't effect the game at runtime

	void Read(wchar& variable); // the makefile will use short instead, but IntelliSense fail to detect this
#endif

private:

	template<typename T>
	void ReadXmlEnum(T& variable);
	void ReadXmlEnum(int& iVariable, JITarrayTypes eType);

	void Read(byte* var, unsigned int iSize);
	int ReadBytes(int iNumBytes);
	unsigned int ReadUnsignedBytes(int iNumBytes);

	SavegameClassTypes m_eClassType;

	CvSavegameReaderBase& m_ReaderBase;
};

class CvSavegameWriter
{
public:
	CvSavegameWriter(CvSavegameWriterBase& writerbase);
	CvSavegameWriter(const CvSavegameWriter& writer);

	void AssignClassType(SavegameClassTypes eType);

	template<enum T>
	void Write(T variable);

	void Write(int iVar);
	void Write(short iVar);
	void Write(char iVar);
	void Write(unsigned int iVar);
	void Write(unsigned short iVar);
	void Write(byte iVar);

	void Write(bool bVar);

	void Write(CvString& szString);
	void Write(CvWString& szString);

	void Write(BoolArray& baArray);
	
	template<class T>
	void Write(JustInTimeArray<T>& jitArray);

	void Write(SavegameVariableTypes eType);
	void Write(SavegameVariableTypes eType, CvString& szString);
	void Write(SavegameVariableTypes eType, CvWString& szString);
	void Write(SavegameVariableTypes eType, BoolArray& baArray);
	void Write(SavegameVariableTypes eType, PlayerBoolArray& array);
	void Write(SavegameVariableTypes eType, IDInfo& idInfo);

	template<class T>
	void Write(SavegameVariableTypes eType, T eVariable, T eDefault);

	template<class T>
	void Write(SavegameVariableTypes eType, JustInTimeArray<T>& jitArray);
	
	// enum conversion
	void GenerateTranslationTable();
	void WriteTranslationTable();

	// everything linked to xml file enums
	void Write(ArtStyleTypes         variable) { WriteXmlEnum(variable); }
	void Write(BonusTypes            variable) { WriteXmlEnum(variable); }
	void Write(BuildTypes            variable) { WriteXmlEnum(variable); }
	void Write(BuildingTypes         variable) { WriteXmlEnum(variable); }
	void Write(BuildingClassTypes    variable) { WriteXmlEnum(variable); }
	void Write(SpecialBuildingTypes  variable) { WriteXmlEnum(variable); }
	void Write(CivEffectTypes        variable) { WriteXmlEnum(variable); }
	void Write(CivicTypes            variable) { WriteXmlEnum(variable); }
	void Write(CivicOptionTypes      variable) { WriteXmlEnum(variable); }
	void Write(CivilizationTypes     variable) { WriteXmlEnum(variable); }
	void Write(ClimateTypes          variable) { WriteXmlEnum(variable); }
	void Write(ColorTypes            variable) { WriteXmlEnum(variable); }
	void Write(CultureLevelTypes     variable) { WriteXmlEnum(variable); }
	void Write(DiplomacyTypes        variable) { WriteXmlEnum(variable); }
	void Write(EmphasizeTypes        variable) { WriteXmlEnum(variable); }
	void Write(EraTypes              variable) { WriteXmlEnum(variable); }
	void Write(EuropeTypes           variable) { WriteXmlEnum(variable); }
	void Write(EventTypes            variable) { WriteXmlEnum(variable); }
	void Write(EventTriggerTypes     variable) { WriteXmlEnum(variable); }
	void Write(FatherTypes           variable) { WriteXmlEnum(variable); }
	void Write(FatherPointTypes      variable) { WriteXmlEnum(variable); }
	void Write(FeatureTypes          variable) { WriteXmlEnum(variable); }
	void Write(GameOptionTypes       variable) { WriteXmlEnum(variable); }
	void Write(GameSpeedTypes        variable) { WriteXmlEnum(variable); }
	void Write(GoodyTypes            variable) { WriteXmlEnum(variable); }
	void Write(HandicapTypes         variable) { WriteXmlEnum(variable); }
	void Write(HurryTypes            variable) { WriteXmlEnum(variable); }
	void Write(ImprovementTypes      variable) { WriteXmlEnum(variable); }
	void Write(LeaderHeadTypes       variable) { WriteXmlEnum(variable); }
	void Write(MemoryTypes           variable) { WriteXmlEnum(variable); }
	void Write(PlayerColorTypes      variable) { WriteXmlEnum(variable); }
	void Write(PlayerOptionTypes     variable) { WriteXmlEnum(variable); }
	void Write(ProfessionTypes       variable) { WriteXmlEnum(variable); }
	void Write(PromotionTypes        variable) { WriteXmlEnum(variable); }
	void Write(RouteTypes            variable) { WriteXmlEnum(variable); }
	void Write(SeaLevelTypes         variable) { WriteXmlEnum(variable); }
	void Write(TerrainTypes          variable) { WriteXmlEnum(variable); }
	void Write(TraitTypes            variable) { WriteXmlEnum(variable); }
	void Write(UnitTypes             variable) { WriteXmlEnum(variable); }
	void Write(UnitAITypes           variable) { WriteXmlEnum(variable); }
	void Write(UnitClassTypes        variable) { WriteXmlEnum(variable); }
	void Write(UnitCombatTypes       variable) { WriteXmlEnum(variable); }
	void Write(SpecialUnitTypes      variable) { WriteXmlEnum(variable); }
	void Write(VictoryTypes          variable) { WriteXmlEnum(variable); }
	void Write(YieldTypes            variable) { WriteXmlEnum(variable); }
	void Write(WorldSizeTypes        variable) { WriteXmlEnum(variable); }

private:

	template<typename T>
	void WriteXmlEnum(T variable);
	void WriteXmlEnum(int iVariable, JITarrayTypes eType);
	void Write(byte*var, unsigned int iSize);

	SavegameClassTypes m_eClassType;

	std::vector<byte>& m_vector;
};

//
// Inline functions to allow easy handling of templates
//

//
// Reader
//

template<typename T>
inline void CvSavegameReader::ReadXmlEnum(T& variable)
{
	int iBuffer;
	ReadXmlEnum(iBuffer, getJITarrayType(variable));
	variable = static_cast<T>(iBuffer);
}

template<typename T>
inline T CvSavegameReader::ReadBitfield(T variable)
{
	Read(variable);
	return variable;
}

template<class T>
inline void CvSavegameReader::Read(JustInTimeArray<T>& jitArray)
{
	jitArray.Read(this);
}



//
// Writer
//

template<enum T>
inline void CvSavegameWriter::Write(T variable)
{
	Write((byte*)&variable, sizeof(T));
}

template<class T>
inline void CvSavegameWriter::Write(JustInTimeArray<T>& jitArray)
{
	jitArray.Write(this);
}

template<class T>
inline void CvSavegameWriter::Write(SavegameVariableTypes eType, T eVariable, T eDefault)
{
	if (eVariable != eDefault)
	{
		Write(eType);
		Write(eVariable);
	}
}

template<class T>
inline void CvSavegameWriter::Write(SavegameVariableTypes eType, JustInTimeArray<T>& jitArray)
{
	if (jitArray.hasContent())
	{
		Write(eType);
		Write(jitArray);
	}
}

template<typename T>
inline void CvSavegameWriter::WriteXmlEnum(T variable)
{
	WriteXmlEnum(variable, getJITarrayType(variable));
}

///
/// base classes
/// do not work with these directly. Make once instance when called from the exe and that's it.
/// Instantly make an instance of the reader/writer with a reference to the base class and then use the reader/writer instead.
///
/// The idea is that the reader/writer will make a new instance for each function call.
/// Since they don't actually contain data, but rather references to the data in the base class, it works like it's just one instance.
/// However since it's one instance for each function call, it will be possible to add variables, which are local to the function in question.
///
/// This allows the reader/writer to be aware of which class it's working on without losing this info by calling some other classes.
/// For instance CvMap knows it's CvMap. It calls CvPlot multiple times, which then knows it's CvPlot, but when it returns, it's back to CvMap without any extra code.
///

class CvSavegameReaderBase
{
	friend class CvSavegameReader;
public:
	CvSavegameReaderBase(FDataStreamBase* pStream);

	~CvSavegameReaderBase();

private:

	void Read(byte* var, unsigned int iSize);

	FDataStreamBase* m_pStream;
	byte* m_Memory;
	byte* m_MemoryAllocation;
	byte *m_MemoryEnd;
	unsigned int m_iSize;
};

class CvSavegameWriterBase
{
	friend class CvSavegameWriter;
public:
	CvSavegameWriterBase(FDataStreamBase* pStream);

	void WriteFile();

private:

	FDataStreamBase* m_pStream;
	std::vector<byte> m_vector;
};

#endif