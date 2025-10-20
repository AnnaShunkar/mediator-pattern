#include <iostream>
#include <string>

using namespace std;
 //інтерфейс//
class IMediator {
public: 
    virtual void notify(const string& sender, const string& event) = 0;
	virtual ~IMediator() = default;
};
//базовий клас//
class Component {
protected:
	IMediator* mediator = nullptr;
public:
	void setMediator(IMediator* m) {
		mediator = m;
	}
};
//конкретні компоненти//
class Button : public Component {
public:
    void click() {
        cout << "Button clicked." << endl;
        if (mediator) mediator->notify("Button", "click");
    }
};

class TextBox : public Component {
public:
    void clear() {
        cout << "TextBox cleared." << endl;
    }

    void fill(const std::string& text) {
        cout << "TextBox filled with: " << text << endl;
    }
};
class UIControlMediator : public IMediator {
private:
    Button* button;
    TextBox* textbox;
public:
    UIControlMediator(Button* b, TextBox* t) : button(b), textbox(t) {
        button->setMediator(this);
        textbox->setMediator(this);
    }

    void notify(const string& sender, const string& event) override {
        if (sender == "Button" && event == "click") {
            textbox->clear();
            textbox->fill("Button was clicked");
        }
    }
};
int main() {
    Button button;
    TextBox textbox;
    UIControlMediator mediator(&button, &textbox);
    button.click(); // запускає взаємодію через посередника//

    return 0;
}
