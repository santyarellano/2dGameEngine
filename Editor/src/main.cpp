#include <iostream>
#include "./Constants.h"
#include "./Editor.h"

int main(int argc, char* args[]) {
	Editor* editor = new Editor();

	editor->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	while (editor->IsRunning()) {
		editor->ProcessInput();
		editor->Update();
		editor->Render();
	}

	editor->Destroy();

	return 0;
}
