#pragma once
#include <memory>
#include "EngineDebug.h"

enum EObjectType
{
	LevelManager,
	Level,
	Actor,
	Component,
	Null,
};

class EngineObjectBase : public std::enable_shared_from_this<EngineObjectBase>
{

public:
	EngineObjectBase();
	~EngineObjectBase();

	EngineObjectBase(const EngineObjectBase& _Other) = delete;
	EngineObjectBase(EngineObjectBase&& _Other) noexcept = delete;
	EngineObjectBase& operator=(const EngineObjectBase& _Other) = delete;
	EngineObjectBase& operator=(EngineObjectBase&& _Other) noexcept = delete;

	//���Ǹ� ���� �Լ�
	bool hasTransform()
	{
		return bHasTransform;
	}
 
	//�������� ȣ��Ǵ� �Լ�
	virtual void Init() = 0;
	virtual void Start() = 0;
	virtual void Update(float _DeltaTime) = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
	virtual void End() = 0;
	
	//�߰����� �۾��� �����ϰ� �ʹٸ� �����ε��ؼ� �����ϸ� �ȴ�.
	virtual void OnCreated(){}
	virtual void OnStart(){}
	virtual void OnUpdate(float _DeltaTime){}
	virtual void OnRender(){}
	virtual void OnEnd(){}
	virtual void OnDestroyed(){}

	void SetActivate(bool _bIsActivate)
	{
		//Ȱ��ȭ�� ������ ����
		if (bIsActivated == true && _bIsActivate == false)
		{
			End();
		}
		//Ȱ��ȭ�� ������ ����
		else if (bIsActivated == false && _bIsActivate == true)
		{
			Start();
		}

		bIsActivated = _bIsActivate;
	}

	void SetOwner(std::shared_ptr<EngineObjectBase> _Owner)
	{
		Owner = _Owner;
	}

	std::shared_ptr<EngineObjectBase> GetOwner()
	{
		return Owner;
	}

	EObjectType GetObjectType()
	{
		return ObjectType;
	}

protected:
	void SetHasTransform(bool _bHasTransform)
	{
		if (bHasTransform != -1)
		{
			return;
		}

		bHasTransform = _bHasTransform;
	}

	void SetObjectType(EObjectType _ObjectType)
	{
		if (_ObjectType == EObjectType::Null)
		{
			EngineDebug::LogErrorMsg(L"ObjectType�� NULL�� �� �����ϴ�.");
			return;
		}

		if (ObjectType != EObjectType::Null)
		{
			return;
		}

		ObjectType = _ObjectType;
	}

private:
	unsigned int bIsActivated : 1 = false;
	unsigned int bHasTransform = -1;

	EObjectType ObjectType = EObjectType::Null;

	std::shared_ptr<EngineObjectBase> Owner = nullptr;
};

