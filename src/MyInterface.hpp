//
// Created by Alex Markessinis on 8/3/16.
//

#ifndef TILEMAP_INTERFACE_H
#define TILEMAP_INTERFACE_H

#include <iostream>
#include <stdlib.h>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>

class MyInterface {
public:
    void RunInterface();
    void ButtonClick();

private:
     sfg::SFGUI mysfgui;
    // sfg::Window::Ptr m_window;
    // sfg::Button::Ptr m_button;
};

void MyInterface::RunInterface() {
    printf("Interface running!\n");
    // m_window = sfg::Window::Create();
    // auto box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.f );
    // m_button = sfg::Button::Create( "Click me" );
    // box->Pack( m_button );
    // m_button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &MyInterface::ButtonClick, this ) );
}

void MyInterface::ButtonClick() {
    // m_button->SetLabel( "I was clicked" );
}

#endif //TILEMAP_INTERFACE_H
