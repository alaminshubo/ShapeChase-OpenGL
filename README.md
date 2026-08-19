# Shape Chase: 2D OpenGL Catch Game 🎮

A real-time, 2-player interactive 2D chase game built with **C++** and **OpenGL (GLUT)**. The game features two dynamic geometric shapes competing in a timed arena with custom collision detection and boundary constraints.

---

## 👥 Contributors
* **Sadia Afrin** (ID: `41230301548`)
* **Md. Al Amin** (ID: `41230301816`)

---

## 🕹️ Game Overview & Rules

* **Square (Red/Chaser 1):** Controlled using keyboard inputs (`W`, `A`, `S`, `D`). Moves smoothly within the arena.
* **Triangle (Cyan/Chaser 2):** Controlled via mouse clicks with an interval cooldown to prevent click-spamming.
* **Objective:**
  * If the **Square** tags the Triangle, **Square Wins**.
  * If the **Triangle** tags the Square via click-teleport, **Triangle Wins**.
  * If the **45-second timer** expires without a collision, the match ends in a **Draw (Time Up)**.
* **Restart:** Press `R` at any time or after game-over to reset the match.

---

## ✨ Features
* **Custom 2D Collision Detection:** Uses Euclidean distance with shape radii bounding.
* **Boundary Clamping:** Ensures shapes remain fully within the 500x500 viewport.
* **On-Screen Heads-Up Display (HUD):** Dynamic real-time countdown timer, controls guide, and match-state alerts using GLUT bitmap fonts.
* **60 FPS Refresh Loop:** Driven by `glutTimerFunc` for smooth animation.

---

## 🛠️ Controls

| Action | Control |
| :--- | :--- |
| **Move Square Up** | `W` / `w` |
| **Move Square Down** | `S` / `s` |
| **Move Square Left** | `A` / `a` |
| **Move Square Right** | `D` / `d` |
| **Move Triangle** | `Left Mouse Click` |
| **Restart Game** | `R` / `r` |

---

## 🚀 How to Run

### Prerequisites
Make sure you have a C++ compiler with OpenGL/GLUT libraries installed:
* **Windows:** FreeGLUT / MinGW or Visual Studio
* **Linux:** `sudo apt-get install freeglut3-dev`

### Compilation (GCC/MinGW)
```bash
g++ main.cpp -o ShapeChase -lfreeglut -lopengl32 -lglu32
./ShapeChase
