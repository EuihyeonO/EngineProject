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

	//엔진에서 호출되는 함수
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
	virtual void End() = 0;
	
	//추가적인 작업을 실행하고 싶다면 오버로딩해서 정의하면 된다.
	virtual void OnCreated(){}
	virtual void OnStart(){}
	virtual void OnUpdate(){}
	virtual void OnRender(){}
	virtual void OnEnd(){}
	virtual void OnDestroyed(){}

	void SetActivate(bool _bIsActivate)
	{
		//활성화가 꺼지는 순간
		if (bIsActivated == true && _bIsActivate == false)
		{
			End();
		}
		//활성화가 켜지는 순간
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

