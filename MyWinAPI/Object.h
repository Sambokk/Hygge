#pragma once
#include "pch.h"
#include "EventMgr.h"

class Texture;
class Animator;
class MouseCollider;
class Object
{
	/// <summary>
	/// �ɹ� ���� ����
	/// </summary>
private:
	bool m_isActive;
	float m_depth;

	wstring m_key;
	wstring	m_name;

	string m_cvPath;
	wstring m_imagePath;

	Vector2	m_scale;
	Vector2	m_position;

	Texture* m_texture;
	Animator* m_animator;
	MouseCollider* m_mouseCollider;

	bool m_isObtained = false;

	/// <summary>
	/// �����ڿ� �Ҹ���
	/// </summary>
public:
	Object();
	virtual ~Object();
	friend class EventMgr;

	/// <summary>
	/// �ɹ� �Լ�
	/// </summary>
public:

	void setRemove() { m_isActive = false; }
	bool isRemove() { return !m_isActive; }	//??
	
	float getDepth() { return m_depth; }
	void setDepth(float _depth) { m_depth = _depth; }

	// �ĺ�
	wstring getKey() { return m_key; }
	void setKey(wstring _key) { m_key = _key; }

	wstring getName() { return m_name; }
	void setName(wstring _name) { m_name = _name; }

	// ���
	string getCvPath() { return m_cvPath; }
	void setCvPath(string _cvPath) { m_cvPath = _cvPath; }

	wstring getImagePath() { return m_imagePath; }
	void setImagePath(wstring _imagePath) { m_imagePath = _imagePath; }

	// ũ�� ��ġ
	Vector2	getScale() { return m_scale; }
	void setScale(Vector2 _scale) { m_scale = _scale; }

	Vector2	getPosition() { return m_position; }
	void setPosition(Vector2 _pos) { m_position = _pos; }

	// �ؽ��� ����
	Texture* getTexture() { return m_texture; }
	void setTexture(Texture* _texture) { m_texture = _texture; }
	void createTexture(wstring _key, wstring _path);

	Animator* getAnimator() { return m_animator; }
	void createAnimator();

	MouseCollider* getMouseCollider() { return m_mouseCollider; }
	void createMouseCollider();

	void setObtained(bool _bool) { m_isObtained = _bool; }
	bool getObtained() { return m_isObtained; }

public:
	virtual void	onMouseCollision(Object* _other) {}
	virtual void	onMouseClicked() {}
	virtual void	onMouseFocused() {}
	virtual void	addPerspectiveOffset(Vector2 _offset) {}

	virtual void	initialize(Vector2 _position, const wstring& _key, const wstring& _relativePath);
	virtual void	render(HDC _dc, Graphics* _grapics);

	void			componentRender(HDC _dc, Graphics* _grapics);

	virtual void	update() = 0;
	virtual void	finalUpdate();
};

