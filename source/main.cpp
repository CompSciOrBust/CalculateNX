#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <switch.h>
#include <math.h>
using namespace std;

//Vars
int TouchX = 0;
int TouchY = 0;
float Ans = 0;
SDL_Event event;
SDL_Window *window;
SDL_Renderer *renderer;
int done = 0;
string Answer = " ";
int AnswerTextHeight = 72;
int ButtonX = 0;
int ButtonY = 0;
int ButtonWidth = 0;
int ButtonHeight = 0;
int XSpacer = 50;
int YSpacer = 50;
int OpperandToUse = 0;
int LayOut = 0;
bool PointUsed = false;

bool ButtonPressed()
{
	if(TouchX > ButtonX && TouchX < ButtonX + ButtonWidth && TouchY > ButtonY && TouchY < ButtonY + ButtonHeight) return true;
	else return false;
}

//Do the math
void CalculateAns()
{
	PointUsed = false;
	switch(OpperandToUse)
	{
		//Just store
		case 0:
		Ans = atof(Answer.c_str());
		break;
		//Add
		case 1:
		Ans += atof(Answer.c_str());
		break;
		//Sub
		case 2:
		Ans -= atof(Answer.c_str());
		break;
		//Multi
		case 3:
		Ans = Ans * atof(Answer.c_str());
		break;
		//Div
		case 4:
		Ans = Ans / atof(Answer.c_str());
		break;
	}
}

void DrawButton(string Text, SDL_Renderer *renderer, TTF_Font *AnswerFont)
{
	//Draw button BG
	SDL_SetRenderDrawColor(renderer, 55, 71, 79, 255);
	SDL_Rect ButtonRect = {ButtonX, ButtonY, ButtonWidth, ButtonHeight};
	SDL_RenderFillRect(renderer, &ButtonRect);
	
	//Draw button text
	SDL_Color TextColour = {255, 255, 255};
	SDL_Surface* ButtonTextSurface = TTF_RenderUTF8_Blended_Wrapped(AnswerFont, Text.c_str(), TextColour, 1280);
	SDL_Texture* ButonTextTexture = SDL_CreateTextureFromSurface(renderer, ButtonTextSurface);
	SDL_Rect TitleRect = {ButtonX + (ButtonWidth - ButtonTextSurface->w) / 2, ButtonY + (ButtonHeight - ButtonTextSurface->h) / 2, ButtonTextSurface->w, ButtonTextSurface->h};
	SDL_RenderCopy(renderer, ButonTextTexture, NULL, &TitleRect);
	SDL_DestroyTexture(ButonTextTexture);
	SDL_FreeSurface(ButtonTextSurface);
}

void RemoveTrailingZeros()
{
	//Remove trailing zeros from answer
	int i = Answer.size()-1;
	while(Answer.c_str()[i] == '0')
	{
		Answer.erase(i, 1);
		--i;
	}
	//Remove trailing point
	if(Answer.c_str()[Answer.size()-1] == '.')
	{
		Answer.erase(i, 1);
	}
}

void MakeLayout(TTF_Font *AnswerFont)
{
	switch(LayOut % 2)
	{
		case 0:
		{
		//Draw the buttons
		//Draw the First row
		ButtonHeight = 130;
		ButtonWidth = 150;
		//Seven
		ButtonX = XSpacer;
		ButtonY = AnswerTextHeight + YSpacer;
		DrawButton("7", renderer, AnswerFont);
		if(ButtonPressed())
		{
			Answer = Answer + "7";
		}
		
		//Eight
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("8", renderer, AnswerFont);
		if(ButtonPressed())
		{
			Answer = Answer + "8";
		}
		
		//Nine
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("9", renderer, AnswerFont);
		if(ButtonPressed())
		{
			Answer = Answer + "9";
		}
		
		//Negate
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("±", renderer, AnswerFont);
		if(ButtonPressed())
		{
			//Check if num contains point
			if(Answer.find('.') != std::string::npos)
			{
				float TempFloat = -atof(Answer.c_str());
				Answer = to_string(TempFloat);
			}
			else
			{
				int TempInt = -atoi(Answer.c_str());
				Answer = to_string(TempInt);
			}
		}
		
		//Plus
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("+", renderer, AnswerFont);
		if(ButtonPressed())
		{
			CalculateAns();
			OpperandToUse = 1;
			Answer = " ";
		}
		
		//Minus
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("-", renderer, AnswerFont);
		if(ButtonPressed())
		{
			CalculateAns();
			OpperandToUse = 2;
			Answer = " ";
		}
		
		//Draw the second row
		ButtonX = XSpacer;
		ButtonY += ButtonHeight + YSpacer;
		
		//Four
		DrawButton("4", renderer, AnswerFont);
		if(ButtonPressed())
		{
			Answer = Answer + "4";
		}
		
		//Five
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("5", renderer, AnswerFont);
		if(ButtonPressed())
		{
			Answer = Answer + "5";
		}
		
		//Six
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("6", renderer, AnswerFont);
		if(ButtonPressed())
		{
			Answer = Answer + "6";
		}
		
		//Zero
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("0", renderer, AnswerFont);
		if(ButtonPressed())
		{
			Answer = Answer + "0";
		}
		
		//Multiply
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("X", renderer, AnswerFont);
		if(ButtonPressed())
		{
			CalculateAns();
			OpperandToUse = 3;
			Answer = " ";
		}
		
		//Divide
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("÷", renderer, AnswerFont);
		if(ButtonPressed())
		{
			CalculateAns();
			OpperandToUse = 4;
			Answer = " ";
		}
		
		//Draw the third row
		ButtonX = XSpacer;
		ButtonY += ButtonHeight + YSpacer;
		
		//One
		DrawButton("1", renderer, AnswerFont);
		if(ButtonPressed())
		{
			Answer = Answer + "1";
		}
		
		//Two
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("2", renderer, AnswerFont);
		if(ButtonPressed())
		{
			Answer = Answer + "2";
		}
		
		//Three
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("3", renderer, AnswerFont);
		if(ButtonPressed())
		{
			Answer = Answer + "3";
		}
		
		//Point
		ButtonX += ButtonWidth + XSpacer;
		DrawButton(".", renderer, AnswerFont);
		if(ButtonPressed() && !PointUsed)
		{
			Answer = Answer + ".";
			PointUsed = true;
		}
		
		//Equals
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("=", renderer, AnswerFont);
		if(ButtonPressed())
		{
			CalculateAns();
			Answer = to_string(Ans);
			RemoveTrailingZeros();
			Ans = 0;
		}
		
		//Clear
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("C", renderer, AnswerFont);
		if(ButtonPressed())
		{
			Answer = " ";
			OpperandToUse = 0;
			Ans = 0;
		}
		
		//Draw the more button
		ButtonWidth = ButtonX - XSpacer + ButtonWidth;
		ButtonX = XSpacer;
		ButtonY += ButtonHeight + (YSpacer / 2);
		ButtonHeight = YSpacer * 1.3;
		DrawButton("More", renderer, AnswerFont);
		if(ButtonPressed())
		{
			LayOut++;
		}
		}
		break;
		case 1:
		{
		//Draw the buttons
		//Draw the First row
		ButtonHeight = 130;
		ButtonWidth = 150;
		//Pi
		ButtonX = XSpacer;
		ButtonY = AnswerTextHeight + YSpacer;
		DrawButton("π", renderer, AnswerFont);
		if(ButtonPressed())
		{
			Answer = Answer + "3.14159265359";
		}
		
		//Euler's number
		ButtonX += ButtonWidth + XSpacer;
		ButtonY = AnswerTextHeight + YSpacer;
		DrawButton("e", renderer, AnswerFont);
		if(ButtonPressed())
		{
			Answer = Answer + "2.71828182845";
		}
		
		//TODO: Implement Sine, Cosine, and Tangent
		
		//Draw the second row
		ButtonX = XSpacer;
		ButtonY += ButtonHeight + YSpacer;
		
		//Square
		DrawButton("x²", renderer, AnswerFont);
		if(ButtonPressed())
		{
			//Check if num contains point
			if(Answer.find('.') != std::string::npos)
			{
				float TempFloat = atof(Answer.c_str());
				Answer = to_string(TempFloat * TempFloat);
			}
			else
			{
				int TempInt = atoi(Answer.c_str());
				Answer = to_string(TempInt * TempInt);
			}
		}
		
		//Square root
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("²√", renderer, AnswerFont);
		if(ButtonPressed())
		{
			//Check if num contains point
			if(Answer.find('.') != std::string::npos)
			{
				float TempFloat = atof(Answer.c_str());
				Answer = to_string(sqrt(TempFloat));
			}
			else
			{
				int TempInt = atoi(Answer.c_str());
				Answer = to_string(sqrt(TempInt));
			}
			RemoveTrailingZeros();
		}
		
		//Draw the third row
		ButtonX = XSpacer;
		ButtonY += ButtonHeight + YSpacer;
		
		//Cube
		DrawButton("x³", renderer, AnswerFont);
		if(ButtonPressed())
		{
			//Check if num contains point
			if(Answer.find('.') != std::string::npos)
			{
				float TempFloat = atof(Answer.c_str());
				Answer = to_string(TempFloat * TempFloat * TempFloat);
			}
			else
			{
				int TempInt = atoi(Answer.c_str());
				Answer = to_string(TempInt * TempInt * TempInt);
			}
		}
		
		//Cube root
		ButtonX += ButtonWidth + XSpacer;
		DrawButton("³√", renderer, AnswerFont);
		if(ButtonPressed())
		{
			//Check if num contains point
			if(Answer.find('.') != std::string::npos)
			{
				float TempFloat = atof(Answer.c_str());
				Answer = to_string(cbrt(TempFloat));
			}
			else
			{
				int TempInt = atoi(Answer.c_str());
				Answer = to_string(cbrt(TempInt));
			}
			RemoveTrailingZeros();
		}
		
		//Draw the Less button
		ButtonWidth = ButtonX - XSpacer + ButtonWidth;
		ButtonX = XSpacer;
		ButtonY += ButtonHeight + (YSpacer / 2);
		ButtonHeight = YSpacer * 1.3;
		DrawButton("More", renderer, AnswerFont);
		if(ButtonPressed())
		{
			LayOut++;
		}
		}
		break;
	}
}

int main(int argc, char *argv[])
{
	//Init
	romfsInit();
	TTF_Init();
	
	//Font for buttons and answer
	TTF_Font *AnswerFont = TTF_OpenFont("romfs:/font.ttf", 48);
	SDL_Color TextColour = {0, 0, 0};
	
    // mandatory at least on switch, else gfx is not properly closed
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        SDL_Log("SDL_Init: %s\n", SDL_GetError());
        return -1;
    }
	
	//Create SDL window the size of the switch's screen.
    window = SDL_CreateWindow("sdl2_gles2", 0, 0, 1280, 720, 0);
    if (!window) {
        SDL_Log("SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // create a renderer (OpenGL ES2)
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // open CONTROLLER_PLAYER_1 and CONTROLLER_PLAYER_2
    // when railed, both joycons are mapped to joystick #0,
    // else joycons are individually mapped to joystick #0, joystick #1, ...
    // https://github.com/devkitPro/SDL/blob/switch-sdl2/src/joystick/switch/SDL_sysjoystick.c#L45
    for (int i = 0; i < 2; i++) {
        if (SDL_JoystickOpen(i) == NULL) {
            SDL_Log("SDL_JoystickOpen: %s\n", SDL_GetError());
            SDL_Quit();
            return -1;
        }
    }

	//Vars
	bool FirstLoop = true;
    while (!done)
	{
		bool EventHasOccured = false;
        while (SDL_PollEvent(&event))
		{
            switch (event.type)
			{
				case SDL_FINGERDOWN:
				TouchX = event.tfinger.x * 1280;
				TouchY = event.tfinger.y * 720;
				EventHasOccured = true;
				break;

                case SDL_JOYBUTTONDOWN:
                    SDL_Log("Joystick %d button %d down\n",
                            event.jbutton.which, event.jbutton.button);
                    // https://github.com/devkitPro/SDL/blob/switch-sdl2/src/joystick/switch/SDL_sysjoystick.c#L52
                    // seek for joystick #0
                    if (event.jbutton.which == 0)
					{
						if (event.jbutton.button == 10)
						{
                            // (+) button down
                            done = 1;
                        }
                    }
                    break;
            }
        }

		//Clear the frame
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // fill window bounds
        SDL_SetRenderDrawColor(renderer, 38, 50, 56, 255);
        SDL_Rect Fill = {0, 0, 1280, 720};
        SDL_RenderFillRect(renderer, &Fill);

		//Draw the answer
		SDL_SetRenderDrawColor(renderer, 176, 190, 197, 255);
		SDL_Rect AnswerRect = {0,0, 1280, AnswerTextHeight};
		SDL_RenderFillRect(renderer, &AnswerRect);
		
		SDL_Surface* AnswerTextSurface = TTF_RenderText_Blended_Wrapped(AnswerFont, Answer.c_str(), TextColour, 1280);
		SDL_Texture* AnswerTextTexture = SDL_CreateTextureFromSurface(renderer, AnswerTextSurface);
		SDL_Rect TitleRect = {1280 - AnswerTextSurface->w, (AnswerTextHeight - AnswerTextSurface->h) / 2, AnswerTextSurface->w, AnswerTextSurface->h};
		SDL_RenderCopy(renderer, AnswerTextTexture, NULL, &TitleRect);
		SDL_DestroyTexture(AnswerTextTexture);
		SDL_FreeSurface(AnswerTextSurface);
		
		MakeLayout(AnswerFont);
		
		//Reset the touch position
		TouchX = 0;
		TouchY = 0;
		
		//Only render frame if event has occured to save power (Or first loop)
		//TODO: Fix
		//if(EventHasOccured || FirstLoop)
		{
			//Render the frame
			SDL_RenderPresent(renderer);
			FirstLoop = false;
		}
    }
	
	//Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
