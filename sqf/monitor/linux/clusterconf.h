///////////////////////////////////////////////////////////////////////////////
//
// @@@ START COPYRIGHT @@@
//
// (C) Copyright 2009-2015 Hewlett-Packard Development Company, L.P.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
// @@@ END COPYRIGHT @@@
//
///////////////////////////////////////////////////////////////////////////////

#ifndef CLUSTERCONF_H_
#define CLUSTERCONF_H_

#include <stdlib.h>
#include <sqlite3.h>

#include "lnodeconfig.h"
#include "pnodeconfig.h"
#include "persistconfig.h"

#define MAX_TOKEN   132
#define PERSIST_PROCESS_KEYS       "PERSIST_PROCESS_KEYS"
#define PERSIST_PROCESS_NAME_KEY   "PROCESS_NAME"
#define PERSIST_PROCESS_TYPE_KEY   "PROCESS_TYPE"
#define PERSIST_PROGRAM_NAME_KEY   "PROGRAM_NAME"
#define PERSIST_REQUIRES_DTM       "REQUIRES_DTM"
#define PERSIST_STDOUT_KEY         "STDOUT"
#define PERSIST_RETRIES_KEY        "PERSIST_RETRIES"
#define PERSIST_ZONES_KEY          "PERSIST_ZONES"

class CClusterConfig  : public CPNodeConfigContainer
                      , public CLNodeConfigContainer
                      , public CPersistConfigContainer
{
public:

    CClusterConfig( void );
    ~CClusterConfig( void );

    inline sqlite3 *GetConfigDb( void ){ return ( db_ ); }
    bool            Initialize( void );
    bool            LoadConfig( void );
    inline bool     IsConfigReady( void ) { return ( configReady_ ); }

protected:
private:

    bool       configReady_; // true when configuration loaded
    bool       excludedCores_;
    bool       newPNodeConfig_;
    bool       newLNodeConfig_;
    int        currNid_;
    int        currPNid_;
    int        currSPNid_;
    char       currNodename_[MPI_MAX_PROCESSOR_NAME];
    cpu_set_t  currExcludedCoreMask_;
    cpu_set_t  currCoreMask_;
    int        currProcessor_;
    ZoneType   currZoneType_;
    CPNodeConfig *currPNodeConfig_;
    int        prevNid_;
    int        prevPNid_;
    int        prevSPNid_;
    char       prevNodename_[MPI_MAX_PROCESSOR_NAME];
    cpu_set_t  prevExcludedCoreMask_;
    cpu_set_t  prevCoreMask_;
    int        prevProcessor_;
    ZoneType   prevZoneType_;
    CPNodeConfig *prevPNodeConfig_;
    int        sparePNid_[MAX_NODES];
    int        spareIndex_;
    CLNodeConfig *lnodeConfig_;
    char            persistPrefix_[MAX_PERSIST_KEY_STR];
    char            processNamePrefix_[MAX_PERSIST_VALUE_STR];
    char            processNameFormat_[MAX_PERSIST_VALUE_STR];
    char            stdoutPrefix_[MAX_PERSIST_VALUE_STR];
    char            stdoutFormat_[MAX_PERSIST_VALUE_STR];
    char            programName_[MAX_PERSIST_VALUE_STR];
    char            zoneFormat_[MAX_PERSIST_VALUE_STR];
    PROCESSTYPE     processType_;
    bool            requiresDTM_;
    int             persistRetries_;
    int             persistWindow_;
    CPersistConfig *persistConfig_;

    sqlite3   *db_;

    void  AddNodeConfiguration( bool spareNode );
    void  AddPersistConfiguration( void );
    PROCESSTYPE GetProcessType( const char *processtype );
    bool  ProcessLNode( int nid
                      , int pnid
                      , const char *nodename
                      , int excfirstcore
                      , int exclastcore
                      , int firstcore
                      , int lastcore
                      , int processors
                      , int roles );
    bool  ProcessSNode( int pnid
                      , const char *nodename
                      , int excfirstcore
                      , int exclastcore
                      , int spnid );
    bool  ProcessPersist( void );
    bool  ProcessPersistData( const char *persistkey
                            , const char *persistvalue );
};

#endif /* CLUSTERCONF_H_ */
