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

#ifndef CIVTask_h
#define CIVTask_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>

class CIVPed;
class IVPed;

class CTaskManager;

class IVEvent
{
public:
	DWORD	m_field4;
	BYTE	m_field8;

	virtual ~IVEvent();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
};


class CIVEvent
{
private:
	IVEvent * m_pEvent;

public:
	CIVEvent();
	CIVEvent(IVEvent * pEvent);
	~CIVEvent();

	void      SetEvent(IVEvent * pEvent) { m_pEvent = pEvent; };
	IVEvent * GetEvent() { return m_pEvent; }
};


const char * GetTaskName(int iTaskType);

class IVTask
{
public:
	IVTask *        m_pParent;
	//PAD(IVTask, pad0, 0x104); // incorrect (probably the biggest task size possible?)
	// 0xE = pPed? // incorrect

	virtual			~IVTask();
	virtual IVTask* Clone();
	virtual bool	IsSimple();
	virtual int		GetType();
	virtual void	Function4();
	virtual bool	MakeAbortable(IVPed * pPed, int iAbortPriority, IVEvent * pEvent);
	virtual float	Function6(int a1);
	virtual int		Function7(int a1);
	virtual void	Function8(int a1);
	virtual int		Function9();
	virtual bool	Function10(); // *(this + 24) > 0.0;
	virtual int		Function11(); // get this+20
	virtual int		Function12();
	virtual bool	Function13(int a1, int a2);
	virtual int		Function14();
	virtual int		Function15();
	virtual int		Function16(int a2);
};
class IVTaskSimple : public IVTask
{
public:
	virtual ~IVTaskSimple();
	virtual void ProcessPed(IVPed * pPed);
	virtual void Function18();
	virtual void Function19();
};

class IVTaskComplex : public IVTask
{
public:
	IVTask * m_pSubTask;
	virtual					~IVTaskComplex();
	virtual void			SetSubTask(IVTask* pTask);
	virtual IVTask*			CreateNextSubTask(IVPed* pPed);
	virtual IVTask*			CreateFirstSubTask(IVPed* pPed);
	virtual IVTask*			ControlSubTask(IVPed* pPed);
};

class CIVTask
{
private:
	IVTask * m_pTask;

public:
	CIVTask();
	CIVTask(IVTask * pTask);
	~CIVTask();

	void			SetTask(IVTask * pTask);
	IVTask *		GetTask();

	void			Create();
	void			Destroy();
	CIVTask *		GetParent();
	CIVTask *		Clone();
	bool			IsSimple();
	int				GetType();
	const char *	GetName();
	bool			MakeAbortable(CIVPed * pPed, int iAbortPriority, CIVEvent * pEvent = NULL);
	void			SetAsPedTask(CIVPed * pPed, int iTaskPriority, bool bForceNewTask = false);
	void			SetAsPedTaskSecondary(CIVPed * pPed, int iTaskPriority);
};

class CIVTaskSimple : public CIVTask
{
public:
	CIVTaskSimple() : CIVTask() {}
	CIVTaskSimple(IVTaskSimple * pTask) : CIVTask(pTask) {}

	bool ProcessPed(CIVPed * pPed);
};

class CIVTaskComplex : public CIVTask
{
public:
	CIVTaskComplex() : CIVTask() {}
	CIVTaskComplex(IVTaskComplex * pTask) : CIVTask(pTask) {}

	CIVTask * GetSubTask();
	void      SetSubTask(CIVTask * pSubTask);
	CIVTask * CreateNextSubTask(CIVPed * pPed);
	CIVTask * CreateFirstSubTask(CIVPed * pPed);
	CIVTask * ControlSubTask(CIVPed * pPed);
};

#endif // CIVTask_h