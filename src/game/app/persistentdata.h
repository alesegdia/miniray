#pragma once

class RunPersistentData
{
public:
	void IncreaseFloor()
	{
		m_currentFloor++;
	}

	void ResetFloor()
	{
		m_currentFloor = 0;
	}

	int GetCurrentFloor()
	{
		return m_currentFloor;
	}

private:
	int m_currentFloor = 0;

};

class PlayerPersistentData
{
public:

	static PlayerPersistentData& GetInstance()
	{
		return s_instance;
	}

	RunPersistentData& GetRunPersistentData()
	{
		return s_instance.m_runPersistentData;
	}

private:
	PlayerPersistentData()
	{

	}

	RunPersistentData m_runPersistentData;
	static PlayerPersistentData s_instance;

};