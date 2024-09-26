#pragma once
#include <memory>

class EngineObjectBase : public std::enable_shared_from_this<EngineObjectBase>
{

public:
	EngineObjectBase();
	~EngineObjectBase();

	EngineObjectBase(const EngineObjectBase& _Other) = delete;
	EngineObjectBase(EngineObjectBase&& _Other) noexcept = delete;
	EngineObjectBase& operator=(const EngineObjectBase& _Other) = delete;
	EngineObjectBase& operator=(EngineObjectBase&& _Other) noexcept = delete;

	//�������� ȣ��Ǵ� �Լ�
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
	virtual void End() = 0;
	
	//�߰����� �۾��� �����ϰ� �ʹٸ� �����ε��ؼ� �����ϸ� �ȴ�.
	virtual void OnCreated(){}
	virtual void OnStart(){}
	virtual void OnUpdate(){}
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

protected:

private:
	unsigned int bIsActivated : 1 = false;
	std::shared_ptr<EngineObjectBase> Owner = nullptr;
};

