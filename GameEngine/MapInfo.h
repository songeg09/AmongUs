#pragma once
#include "pch.h"
#include "PathManager.h"

struct MapInfo
{
	Vector2								m_vec2PlayerStart;

	std::vector<Vector2>				m_arrWayPoints;

	std::vector<std::vector<Vector2>>	m_arrAllWallVertices;
	std::vector<Vector2>				m_arrVent;
	std::vector<Vector2>				m_arrNumberSequencePos;
	std::vector<Vector2>				m_arrDataUploadPos;
	std::vector<Vector2>				m_arrTimedButtonsPos;

	void Load()
	{
		// 멤버 변수 초기화
		m_vec2PlayerStart = { -1,-1 };
		m_arrWayPoints.clear();
		m_arrAllWallVertices.clear();
		m_arrVent.clear();
		m_arrNumberSequencePos.clear();
		m_arrDataUploadPos.clear();
		m_arrTimedButtonsPos.clear();

		std::wifstream _loadFile;
		_loadFile.open(PathManager::GetInstance()->GetContentpath() + ConstValue::strDataPath + ConstValue::strMapDataFileName);
		if (_loadFile.is_open())
		{
			if (_loadFile.peek() == std::wifstream::traits_type::eof())
			{
				// 빈 파일이므로 그냥 기본값으로 설정
				_loadFile.close();
				return;
			}

			int x, y, n, m;

			// Player Start
			_loadFile >> x >> y;
			m_vec2PlayerStart = Vector2(x, y);

			// Way Points
			_loadFile >> n;
			m_arrWayPoints.reserve(n);
			for (int i = 0; i < n; ++i)
			{
				_loadFile >> x >> y;
				m_arrWayPoints.push_back(Vector2(x, y));
			}

			// Wall Vertices
			_loadFile >> n;
			for (int i = 0; i < n; ++i)
			{
				std::vector<Vector2> arrCurWall;
				_loadFile >> m;
				for (int j = 0; j < m; ++j)
				{
					_loadFile >> x >> y;
					arrCurWall.push_back(Vector2(x, y));
				}
				m_arrAllWallVertices.push_back(arrCurWall);
			}

			// Vents
			_loadFile >> n;
			m_arrVent.reserve(n);
			for (int i = 0; i < n; ++i)
			{
				_loadFile >> x >> y;
				m_arrVent.push_back(Vector2(x, y));
			}

			// Number Sequence
			_loadFile >> n;
			m_arrNumberSequencePos.reserve(n);
			for (int i = 0; i < n; ++i)
			{
				_loadFile >> x >> y;
				m_arrNumberSequencePos.push_back(Vector2(x, y));
			}

			// Data Upload
			_loadFile >> n;
			m_arrDataUploadPos.reserve(n);
			for (int i = 0; i < n; ++i)
			{
				_loadFile >> x >> y;
				m_arrDataUploadPos.push_back(Vector2(x, y));
			}

			// Timed Buttons
			_loadFile >> n;
			m_arrTimedButtonsPos.reserve(n);
			for (int i = 0; i < n; ++i)
			{
				_loadFile >> x >> y;
				m_arrTimedButtonsPos.push_back(Vector2(x, y));
			}

			_loadFile.close();
		}
	}

	void Save()
	{

		std::wofstream _saveFile;
		_saveFile.open(PathManager::GetInstance()->GetContentpath() + ConstValue::strDataPath + ConstValue::strMapDataFileName, std::ios::out);
		if (_saveFile.is_open())
		{
			// Player Start
			_saveFile << (int)m_vec2PlayerStart.m_fx << L" " << (int)m_vec2PlayerStart.m_fy << '\n';

			// Way Points
			_saveFile << m_arrWayPoints.size() << '\n';
			for (Vector2 pos : m_arrWayPoints)
				_saveFile << (int)pos.m_fx << L" " << (int)pos.m_fy << '\n';

			// Wall Vertices
			_saveFile << m_arrAllWallVertices.size() << '\n';
			for (int i = 0; i < m_arrAllWallVertices.size(); ++i)
			{
				_saveFile << m_arrAllWallVertices[i].size() << '\n';
				for(Vector2 pos: m_arrAllWallVertices[i])
					_saveFile << (int)pos.m_fx << L" " << (int)pos.m_fy << '\n';
			}

			// Vents
			_saveFile << m_arrVent.size() << '\n';
			for (Vector2 pos : m_arrVent)
				_saveFile << (int)pos.m_fx << L" " << (int)pos.m_fy << '\n';

			// Number Sequence
			_saveFile << m_arrNumberSequencePos.size() << '\n';
			for (Vector2 pos : m_arrNumberSequencePos)
				_saveFile << (int)pos.m_fx << L" " << (int)pos.m_fy << '\n';

			// Data Upload
			_saveFile << m_arrDataUploadPos.size() << '\n';
			for (Vector2 pos : m_arrDataUploadPos)
				_saveFile << (int)pos.m_fx << L" " << (int)pos.m_fy << '\n';

			// Timed Buttons
			_saveFile << m_arrTimedButtonsPos.size() << '\n';
			for (Vector2 pos : m_arrTimedButtonsPos)
				_saveFile << (int)pos.m_fx << L" " << (int)pos.m_fy << '\n';

			_saveFile.close();
		}
	}
};

