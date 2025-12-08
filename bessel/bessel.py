import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from scipy.special import jn, jn_zeros

# ---------------------
# 🎯 사용자 설정 부분
n = 2  # 각 방향 모드 (꽃잎 개수)
m = 1  # 반지름 방향 모드 (동심원 개수)
A = 1.0  # 진폭
frame_count = 100  # 프레임 수
interval_ms = 50  # 프레임 간 시간 간격 (ms)
# ---------------------

# 격자 설정 (극좌표계 -> 직교좌표계)
r = np.linspace(0, 1, 300)
theta = np.linspace(0, 2 * np.pi, 300)
R, Theta = np.meshgrid(r, theta)
X = R * np.cos(Theta)
Y = R * np.sin(Theta)

# Bessel 함수의 고유 영점
alpha_nm = jn_zeros(n, m)[-1]

# 시간 배열
t_values = np.linspace(0, 2 * np.pi, frame_count)

# 진동 함수 정의
def displacement(t):
    return A * jn(n, alpha_nm * R) * np.cos(n * Theta) * np.cos(t)

# 애니메이션 설정
fig = plt.figure(figsize=(6, 5))
ax = fig.add_subplot(111, projection='3d')
ax.set_zlim(-1, 1)
ax.axis('off')
surf = [ax.plot_surface(X, Y, displacement(0), cmap='viridis', edgecolor='none')]

def update(frame):
    ax.collections.clear()
    Z = displacement(t_values[frame])
    surf[0] = ax.plot_surface(X, Y, Z, cmap='viridis', edgecolor='none')
    ax.set_title(f"Mode (n={n}, m={m}) | Frame {frame+1}/{frame_count}")
    return surf

ani = FuncAnimation(fig, update, frames=frame_count, interval=interval_ms, blit=False)
plt.show()
