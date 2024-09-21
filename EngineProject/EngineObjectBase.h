#pragma once

class EngineObjectBase
{

public:

	EngineObjectBase();
	~EngineObjectBase();

	EngineObjectBase(const EngineObjectBase& _Other) = delete;
	EngineObjectBase(EngineObjectBase&& _Other) noexcept = delete;
	EngineObjectBase& operator=(const EngineObjectBase& _Other) = delete;
	EngineObjectBase& operator=(EngineObjectBase&& _Other) noexcept = delete;

	virtual void OnCreated() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;
	virtual void OnDestroyed() = 0;

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

protected:

private:
	unsigned int bIsActivated : 1 = false;

};

