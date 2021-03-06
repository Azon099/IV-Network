/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CPedTaskManager_h
#define CPedTaskManager_h

#include <Common.h>
#include "../GameCommon.h"

#include "CTask.h"

_GAME_BEGIN

class ITask;
class IPed;

class IPedTaskManager
{
public:  
	ITask * m_pPrimaryTasks[TASK_PRIORITY_MAX];    // 00-14
	ITask * m_pSecondaryTasks[TASK_SECONDARY_MAX]; // 14-2C
	ITask * m_pMovementTasks[TASK_MOVEMENT_MAX];   // 2C-38
	IPed * m_pPed;                                 // 38-3C
	PAD(IPedTaskManager, pad0, 0x4);               // 3C-40
};

class CPedTaskManager
{
private:
	IPedTaskManager * m_pPedTaskManager;
	CPed           * m_pPed;

public:
	CPedTaskManager(IPedTaskManager * pPedTaskManager, CPed * pPed);

	void               SetPedTaskManager(IPedTaskManager * pPedTaskManager) { m_pPedTaskManager = pPedTaskManager; }
	IPedTaskManager * GetPedTaskManager() { return m_pPedTaskManager; }
	void               SetPed(CPed * pPed) { m_pPed = pPed; }
	CPed           * GetPed() { return m_pPed; }

	// Primary tasks
	void               SetTask(CTask * pTask, int iType, bool bForceNewTask = false);
	void               RemoveTask(int iType);
	CTask          * GetTask(int iType);

	// Secondary tasks
	void               SetTaskSecondary(CTask * pTask, int iType);
	void               RemoveTaskSecondary(int iType);
	CTask          * GetTaskSecondary(int iType);

	// Movement tasks
	void               SetTaskMovement(CTask * pTask, int iType);
	void               RemoveTaskMovment(int iType);
	CTask          * GetTaskMovement(int iType);

	void               ClearTasks(int iAbortPriority);
};

_GAME_END

#endif // CPedTaskManager_h
