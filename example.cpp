// Copyright (c) 2022 moowool195@gmail.com. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. Neither the name of the University nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

#include <iostream>
#include "timer.h"

int main(int argc, char** argv)
{
	using Ms = std::chrono::milliseconds;

	Timer t; // Begins to time as soon as instanced
	std::cout << "Timer instanced, recording.\nPress [ENTER] to get the recorded time." << std::endl;
	std::cin.get();
	std::cout << "Current recorded time: " << t.get<Ms>() << "ms" << "\n" << std::endl;

	// Pauses the timer, does not record time anymore
	// It can be toggled back on by running the method again
	t.pause();
	std::cout << "Paused.\nPress [ENTER] to get the recorded time." << std::endl;
	std::cin.get();
	std::cout << "Current recorded time: " << t.get<Ms>() << "ms" << "\n" << std::endl;

	// Resets the timer, which also unpauses it.
	t.reset();
	std::cout << "Timer reset.\nPress [ENTER] to get the recorded time." << std::endl;
	std::cin.get();
	std::cout << "Current recorded time: " << t.get<Ms>() << "ms" << std::endl;

	return 0;
}
