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

private:
	int m_currentFloor = 0;

};

class PlayerPersistentData
{
public:

};