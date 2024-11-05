#pragma once
#include "Object.h"
class UI :
    public Object
{
private:
    static bool m_soundPlay;
    float m_time;
    int m_sceneType;

public:
    UI(wstring _name, Vector2 _position, wstring _key, wstring _path, int _scene);
    UI(wstring _name, Vector2 _position, wstring _key, wstring _path, string _cvpath , int _scene);
    ~UI();


public:
    virtual void update();
    virtual void render(HDC _dc, Graphics* _graphic);
    virtual void onMouseClicked();

private:
    void destroyThisWindow();
};

