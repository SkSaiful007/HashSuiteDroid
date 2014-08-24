// This file is part of Hash Suite password cracker,
// Copyright (c) 2011-2013 by Alain Espinosa
//
// Code licensed under GPL version 2

#define CREATE_SCHEMA											\
"CREATE TABLE IF NOT EXISTS Account (							\
    ID INTEGER PRIMARY KEY,								        \
    UserName TEXT NOT NULL,										\
    Hash INTEGER,                                               \
	Fixed INTEGER NOT NULL DEFAULT 0,							\
	Privilege INTEGER NOT NULL DEFAULT 1,						\
	FOREIGN KEY(Hash) REFERENCES Hash(ID),					    \
	UNIQUE(UserName,Hash)										\
);																\
																\
CREATE TABLE IF NOT EXISTS AccountLM (							\
    ID INTEGER PRIMARY KEY,								        \
	LM1 INTEGER,												\
	LM2 INTEGER,												\
	FOREIGN KEY(LM1) REFERENCES Hash(ID),					    \
	FOREIGN KEY(LM2) REFERENCES Hash(ID),					    \
	FOREIGN KEY(ID) REFERENCES Account(ID)					    \
);																\
																\
CREATE TABLE IF NOT EXISTS Tag (								\
    ID INTEGER PRIMARY KEY,									    \
    Name TEXT NOT NULL UNIQUE									\
);																\
																\
CREATE TABLE IF NOT EXISTS TagAccount (							\
    TagID INTEGER,												\
    AccountID INTEGER,											\
	PRIMARY KEY(TagID, AccountID),								\
	FOREIGN KEY(TagID) REFERENCES Tag(ID),					    \
	FOREIGN KEY(AccountID) REFERENCES Account(ID)		        \
);																\
																\
CREATE TABLE IF NOT EXISTS Format (								\
    ID INTEGER PRIMARY KEY,								        \
    Name TEXT NOT NULL UNIQUE,									\
	Description TEXT											\
);																\
																\
CREATE TABLE IF NOT EXISTS Hash (								\
    ID INTEGER PRIMARY KEY,									    \
    Hex TEXT NOT NULL,									        \
	DateInserted DATETIME NOT NULL DEFAULT (datetime('now')),	\
	Type INTEGER NOT NULL,										\
	FOREIGN KEY(Type) REFERENCES Format(ID),				    \
	UNIQUE(Hex,Type)                                            \
);																\
																\
CREATE TABLE IF NOT EXISTS KeyProvider (						\
    ID INTEGER PRIMARY KEY,							            \
    Name TEXT NOT NULL UNIQUE,									\
	Description TEXT											\
);																\
																\
CREATE TABLE IF NOT EXISTS Attack (								\
    ID INTEGER PRIMARY KEY,								        \
    Begin DATETIME NOT NULL DEFAULT (datetime('now')),			\
	End DATETIME,												\
	ElapsedTime INTEGER NOT NULL DEFAULT 0,						\
	ResumeArg TEXT,												\
	Param TEXT,													\
	MinLenght INTEGER,                                          \
	MaxLenght INTEGER,                                          \
	NumKeysServed INTEGER NOT NULL DEFAULT 0,					\
	Provider INTEGER,											\
	Format INTEGER,												\
	FOREIGN KEY(Provider) REFERENCES KeyProvider(ID),           \
	FOREIGN KEY(Format) REFERENCES Format(ID)				    \
);																\
																\
CREATE TABLE IF NOT EXISTS FindHash (							\
    ID INTEGER PRIMARY KEY,								        \
	ClearText TEXT NOT NULL,									\
	ElapsedFind INTEGER NOT NULL,								\
	AttackUsed INTEGER,											\
	FOREIGN KEY(ID) REFERENCES Hash(ID),			            \
	FOREIGN KEY(AttackUsed) REFERENCES Attack(ID)			    \
);																\
																\
CREATE TABLE IF NOT EXISTS Charset (							\
    ID INTEGER PRIMARY KEY,								        \
	Name TEXT NOT NULL UNIQUE,									\
	Value TEXT NOT NULL UNIQUE,									\
	Description TEXT											\
);																\
																\
INSERT OR IGNORE INTO Charset (ID, Name, Value, Description) VALUES (1, 'Lower', 'abcdefghijklmnopqrstuvwxyz', 'Lower Case characters.');			\
INSERT OR IGNORE INTO Charset (ID, Name, Value, Description) VALUES (2, 'Upper', 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'Upper Case characters.');			\
INSERT OR IGNORE INTO Charset (ID, Name, Value, Description) VALUES (3, 'Digit', '0123456789', 'All decimal digits.');								\
INSERT OR IGNORE INTO Charset (ID, Name, Value, Description) VALUES (4, 'Symbol', ' !@#$%^&*()-_+=~`[]{}|:;\"''<>,.?/\\', 'All puntuation symbols.');\
																\
																\
INSERT OR IGNORE INTO Tag (ID, Name) VALUES (14, 'Common');		\
INSERT OR IGNORE INTO Tag (ID, Name) VALUES (29, 'Languages');	\
INSERT OR IGNORE INTO Tag (ID, Name) VALUES (30, 'Huge');		\
																\
CREATE TABLE IF NOT EXISTS WordList (							\
    ID INTEGER PRIMARY KEY,								        \
	Name TEXT NOT NULL UNIQUE,									\
	FileName TEXT NOT NULL UNIQUE,								\
	Url TEXT,													\
	Length INTEGER,												\
	State INTEGER DEFAULT 0,									\
	Category INTEGER DEFAULT 14,								\
	Description TEXT,											\
	FOREIGN KEY(Category) REFERENCES Tag(ID)					\
);																\
																\
																\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (1, 'facebook-names-unique.txt.bz2',				'1', 'http://downloads.skullsecurity.org/passwords/facebook-names-unique.txt.bz2', 479332623, 1, 30);	\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (2, 'wikipedia-wordlist-sraveau-20090325.txt.bz2',	'2', 'http://www.hack3r.com/wordlists/wikipedia-wordlist-sraveau-20090325.txt.bz2', 222575137, 1, 30);	\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (3, 'rockyou.txt.bz2',								'3', 'http://downloads.skullsecurity.org/passwords/rockyou.txt.bz2', 60498886, 1, 30);					\
																																																													\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (4, '500-worst-passwords.txt.bz2',					'4', 'http://downloads.skullsecurity.org/passwords/500-worst-passwords.txt.bz2', 1868, 1, 14);			\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (5, 'GDict_v2.0.7z',								'5', 'http://gdataonline.com/downloads/GDict/GDict_v2.0.7z', 30583890, 1, 14);							\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (6, 'Case_Mutation_Full.7z',						'6', 'http://gdataonline.com/downloads/Case_Mutations/Case_Mutation_Full.7z', 2338538, 1, 14);			\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (7, 'L33t_Dict_Full.7z',							'7', 'http://gdataonline.com/downloads/L33t_Dict/L33t_Dict_Full.7z', 5368366, 1, 14);					\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (8, 'porno.txt.bz2',								'8', 'http://downloads.skullsecurity.org/passwords/porno.txt.bz2', 7158285, 1, 14);						\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (9, 'bible.txt.bz2',								'9', 'https://downloads.skullsecurity.org/passwords/bible.txt.bz2', 42208, 1, 14);						\
																																																							\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (10, 'english.zip',						'10', 'http://apasscracker.com/dictionaries/english.zip', 9295868, 1, 29);				\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (11, 'english.txt.bz2',					'11', 'http://downloads.skullsecurity.org/passwords/english.txt.bz2', 1368101, 1, 29);	\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (12, 'spanish.zip',						'12', 'http://apasscracker.com/dictionaries/spanish.zip', 914020, 1, 29);				\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (13, 'russian.zip',						'13', 'http://apasscracker.com/dictionaries/russian.zip', 1873123, 1, 29);				\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (14, 'french.zip',							'14', 'http://apasscracker.com/dictionaries/french.zip', 386989, 1, 29);				\
INSERT OR IGNORE INTO WordList (ID, Name, FileName, Url, Length, State, Category) VALUES (15, 'german.txt.bz2',						'15', 'http://downloads.skullsecurity.org/passwords/german.txt.bz2', 2371487, 1, 29);	\
																																																							\
																\
																\
CREATE TABLE IF NOT EXISTS PhrasesWordList (					\
    ID INTEGER PRIMARY KEY,								        \
	Name TEXT NOT NULL UNIQUE,									\
	FileName TEXT NOT NULL UNIQUE,								\
	Length INTEGER												\
);																\
																\
CREATE TABLE IF NOT EXISTS Keyboard (							\
    ID INTEGER PRIMARY KEY,								        \
	Name TEXT NOT NULL UNIQUE,									\
	Chars TEXT NOT NULL UNIQUE,									\
	Description TEXT											\
);																\
																\
INSERT OR IGNORE INTO Keyboard (ID, Name, Chars, Description) VALUES (1, 'EN_Qwerty',       '`1234567890-=qwertyuiop[]\\asdfghjkl;''\\zxcvbnm,./', 'English Qwerty keyboard layout');	\
INSERT OR IGNORE INTO Keyboard (ID, Name, Chars, Description) VALUES (2, 'EN_Dvorak',       '`1234567890[]'',.pyfgcrl/=\\aoeuidhtns-\\;qjkxbmwvz', 'English Dvorak keyboard layout');	\
INSERT OR IGNORE INTO Keyboard (ID, Name, Chars, Description) VALUES (3, 'EN_Qwerty_SHIFT', '~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"|ZXCVBNM<>?'  , 'English Qwerty keyboard layout with shift pressed');	\
INSERT OR IGNORE INTO Keyboard (ID, Name, Chars, Description) VALUES (4, 'ES_Qwerty',       '�1234567890''�qwertyuiop`+�asdfghjkl��zxcvbnm,.-'  , 'Spanish Qwerty keyboard layout');	\
INSERT OR IGNORE INTO Keyboard (ID, Name, Chars, Description) VALUES (5, 'FR_Qwerty',       '�&�\"''(-�_��)=azertyuiop^$*qsdfghjklm�*wxcvbn,;:!' , 'French Qwerty keyboard layout');	\
INSERT OR IGNORE INTO Keyboard (ID, Name, Chars, Description) VALUES (6, 'PT_pt_Qwerty',    '\\1234567890''�qwertyuiop+�~asdfghjkl�~zxcvbnm,.-' , 'Portuguese Qwerty keyboard layout');\
INSERT OR IGNORE INTO Keyboard (ID, Name, Chars, Description) VALUES (7, 'PT_br_Qwerty',    '''1234567890-=qwertyuiop�[]asdfghjkl�~]zxcvbnm,.;'  , 'Brazilian Qwerty keyboard layout');	\
																\
CREATE TABLE IF NOT EXISTS Settings (							\
    ID INTEGER PRIMARY KEY,								        \
	Value INTEGER NOT NULL										\
);																\
																\
CREATE TABLE IF NOT EXISTS Batch (								\
    ID INTEGER PRIMARY KEY,								        \
	Name TEXT NOT NULL,											\
	Description TEXT NOT NULL									\
);																\
																\
CREATE TABLE IF NOT EXISTS BatchAttack (						\
    BatchID INTEGER,											\
	AttackID INTEGER,											\
	PRIMARY KEY(BatchID, AttackID)								\
);																\
																\
CREATE TABLE IF NOT EXISTS ReportFormats (						\
    ID INTEGER PRIMARY KEY,								        \
	Format TEXT NOT NULL,										\
	Description TEXT NOT NULL									\
);																\
																\
CREATE TABLE IF NOT EXISTS Reports (							\
    ID INTEGER PRIMARY KEY,								        \
	Name TEXT NOT NULL,											\
	Description TEXT NOT NULL									\
);"
