# [GCJ 2009 #1C] Center of Mass

## 题目描述

你正在研究一群 $N$ 只萤火虫。每只萤火虫都以恒定速度沿直线运动。你站在宇宙的中心，即位置 $(0, 0, 0)$。每只萤火虫的质量都相同，你想知道这群萤火虫的质心距离你的位置（原点）最近会有多近。

你已知每只萤火虫在 $t = 0$ 时的初始位置和速度，且只关心 $t \geq 0$ 的情形。萤火虫们速度恒定，可以自由穿越空间，包括互相穿过和穿过你。设 $M(t)$ 表示 $N$ 只萤火虫在时刻 $t$ 的质心位置，$d(t)$ 表示你的位置到 $M(t)$ 的距离。请你求出 $d(t)$ 的最小值 $d_{\text{min}}$，以及最早使 $d(t) = d_{\text{min}}$ 的时刻 $t_{\text{min}}$。


## 说明/提示

**说明**

给定 $N$ 个点 $(x_i, y_i, z_i)$，它们的质心为 $(x_c, y_c, z_c)$，其中：

- $x_c = (x_1 + x_2 + \ldots + x_N) / N$
- $y_c = (y_1 + y_2 + \ldots + y_N) / N$
- $z_c = (z_1 + z_2 + \ldots + z_N) / N$

**限制条件**

- 输入中的所有数均为整数。
- $1 \leq T \leq 100$
- $x$、$y$、$z$、$v_x$、$v_y$、$v_z$ 的取值范围均为 $-5000$ 到 $5000$，包含端点。

**小数据集（10 分）**

- $3 \leq N \leq 10$

**大数据集（17 分）**

- $3 \leq N \leq 500$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
3
3
3 0 -4 0 0 3
-3 -2 -1 3 0 0
-3 -1 2 0 3 0
3
-5 0 0 1 0 0
-7 0 0 1 0 0
-6 3 0 1 0 0
4
1 2 3 1 2 3
3 2 1 3 2 1
1 0 0 0 0 -1
0 10 0 0 -10 -1```

### 输出

```
Case #1: 0.00000000 1.00000000
Case #2: 1.00000000 6.00000000
Case #3: 3.36340601 1.00000000```

# 题解

## 作者：WsW_ (赞：2)

### 思路
根据质心相关公式，我们可以知道在题目条件下，质心沿直线运动。具体的运动轨迹为射线。  
原问题就变为了求点到射线的最短距离。可以直接通过计算几何的相关公式求解，但十分复杂。  
可以发现，点到射线的最短距离有明显的单调性。要么先减后增，要么一直增。  
在单峰函数上求极值可以使用三分法。  
具体地，对时间进行实数三分。进行三分首先需要确定三分的范围。  
三分的下界显然为 $0$，考虑如何确定上界。  
观察数据范围发现，质心必定处于一个以 $(0,0,0)$ 为中心，边长为 $d=10^4$ 的正方体内；质心某一方向的速度若不为 $0$，则最小为 $\frac{1}{N}=\frac{1}{500}$。  
当时间大于 $N\times d=5\times 10^6$ 时，质心必定已经离开以 $(0,0,0)$ 为中心，直径为 $d=10^4$ 的球形区域，此时质心到中心的距离必定大于一开始质心到中心的距离。  
故三分的上界为 $5\times 10^6$。  

需要特别注意，当速度为 $0$ 时，函数值恒定，应当特判。  

令 $M=N\times d$，则时间复杂度为 $O(T\log M)$。

---
### 代码
```cpp
#include<bits/stdc++.h>
#define pw(x) ((x)*(x))
using namespace std;
typedef double db;
typedef long long ll;

db dis(db pos[3],db v[3],db t){
	db ans=0;
	for(int i=0;i<3;i++)ans+=pw(pos[i]+v[i]*t);
	return ans;
}

void work(){
	int n; cin>>n;
	db pos[3]={0,0,0},v[3]={0,0,0};
	for(int i=0;i<n;i++){
		int x;
		for(int j=0;j<3;j++){
			cin>>x;
			pos[j]+=(db)x/n;
		}
		for(int j=0;j<3;j++){
			cin>>x;
			v[j]+=(db)x/n;
		}
	}
	if(abs(pw(v[0])+pw(v[1])+pw(v[2]))<1e-6){
		cout<<sqrt(dis(pos,v,0))<<" 0\n";
		return;
	}
	db l=0,r=5e6,midl,midr;
	for(int i=0;i<100;++i){
		midl=(2*l+r)/3;
		midr=(l+2*r)/3;
		if(dis(pos,v,midl)<dis(pos,v,midr))r=midr;
		else l=midl;
	}
	cout<<sqrt(dis(pos,v,l))<<' '<<l<<'\n';
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T; cin>>T;
	cout<<fixed<<setprecision(8);
	for(int i=1;i<=T;i++){
		cout<<"Case #"<<i<<": ";
		work();
	}
	return 0;
}
```

---

