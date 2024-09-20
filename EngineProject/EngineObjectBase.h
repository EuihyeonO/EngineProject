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
protected:

private:

};

