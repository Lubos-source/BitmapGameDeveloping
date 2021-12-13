#pragma once
#include <vector>
#include <string> 

class CCfgFile
{
public:
	struct TToken {
		int section;
		char id[255];
		char value[255];
	};
	std::vector <TToken *> m_Tokens;
	int m_NumSections;

	int CislaMapa[24][32];

public:
	int GetNumSections() { return(m_NumSections); }
	int LoadFile(char *name);
	int GetIntValue(int section,char *id);
	void GetStrValue(int section,char *id,char *tmp);

	void GetMapLoad(char* File_name, int mapa[24][32]);

	CCfgFile(void);
	~CCfgFile(void);
};
