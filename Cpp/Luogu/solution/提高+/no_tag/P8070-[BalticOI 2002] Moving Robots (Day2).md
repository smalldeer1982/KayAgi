# [BalticOI 2002] Moving Robots (Day2)

## 题目描述

一些机器人在二维平面上根据指令移动。机器人移动互不影响，甚至同一时刻同一点可能有多个机器人。

移动有两种：
- `S`：向前一步。  
  记当前位置为 $(x, y)$，当前方向为 $C$：若 $C = 0$ 移至 $(x + 1, y)$；若 $C = 90$ 移至 $(x, y + 1)$；若 $C = 180$ 移至 $(x - 1, y)$；若 $C = 270$ 移至 $(x, y - 1)$。
  
- `T D`：方向增加 $D$。  
  即令当前方向 $C \gets (C + D) \bmod 360$。



给定各机器人预设的指令序列，移除一些指令使所有机器人最终位于同一位置，并最小化移除指令数。

## 说明/提示

#### 样例说明

有两个机器人。第一个初始位于 $(2, 0)$，初始方向 $270$，指令序列长度为 $5$；第二个初始位于 $(1, -1)$，初始方向 $0$，指令序列长度为 $8$。至少需要移除两个指令。例如移除第一个机器人第三个指令与第二个机器人第五个指令，此时最终位置为 $(2, 1)$。

#### 数据范围

$2 \le R \le 10$，$1 \le n \le 50$，$-50 \le x, y \le 50$，$C, D \in \lbrace 0, 90, 180, 270 \rbrace$，保证指令格式如题目描述。

#### 提示

[BalticOI](https://boi.cses.fi/contests.php) 2002 Day2 C.

由于自定义计分脚本参数配置，暂不支持 AC WA TLE MLE 外的评测状态显示。如果你得到了此外任何一种评测状态，你将得到 UKE。

Subtask 设置与题目无关，仅为便于自定义积分脚本运行。

## 样例 #1

### 输入

```
2 
2 0 270 5 
S 
T 180 
S 
S 
S 
1 -1 0 8 
S 
S 
T 90 
S 
T 270 
S 
T 90 
S 
```

### 输出

```
2 
2 1 ```

# 题解

## 作者：zzz13579zzz (赞：3)

随到的题目，看没有题解，先来一发

## [P8070 [BalticOI 2002] Moving Robots (Day2)](https://www.luogu.com.cn/problem/P8070)
### 题目描述

有 $R$ 个机器人在二维平面运动，可前进或转向，删除最小的命令个数，使得所有机器人停在同一位置

### 数据范围

$2 \le R \le 10$，$1 \le n \le 50$，$-50 \le x, y \le 50$

- #### 题目分析
  注意到 $n$ 只有 $50$，所以机器人能走到的位置与初始点的曼哈顿距离不会超过 $50$，所以可以暴力枚举能走到的位置，计算最少能删多少命令
- #### 具体实现
  用数组存储每个机器人到达不同位置，朝向不同方向的可删除最小命令数，若不可达，记为 inf

  对于每条命令，机器人上一步可达的位置都会进行此命令，所以遍历一遍数组，进行转移，并将最小命令数 $-1$
  
- #### 细节处理
1. $x,y$ 可能为负数，所以开数组时要加上偏移量
2. 方向可以除以 $90$,变为 $0,1,2,3$ 处理
3. 不能一边遍历一边修改，否则可能会出现还未遍历到的位置已被修改的情况，建议使用 vector 等先存后用

- #### 复杂度分析
   $R$ 个机器人，$n$ 条命令，约有 $n^2$ 个位置可达，加上 $4$ 个方向，$O(Rn^3)$
### code
写的比较凌乱，看上面比较好

```cpp
#include<bits/stdc++.h>
using namespace std;
int r,n,x,y,c,ans[11][210][210][4],d,dd[210][210];
struct wz{int x,y,c,w;};
void wd(int r){
	vector<wz>q;
	for(int x=1;x<=200;x++)
		for(int y=1;y<=200;y++)
			for(c=0;c<4;c++)
				if(ans[r][x][y][c]<=n and ans[r][x][y][c]>0){
					wz kk={x,y,c,ans[r][x][y][c]};
					q.emplace_back(kk);	}								

	for(auto t:q){
		int x=t.x,y=t.y,c=t.c,w=t.w;
		if(c==0)ans[r][x+1][y][c]=min(ans[r][x+1][y][c],w-1);
		if(c==1)ans[r][x][y+1][c]=min(ans[r][x][y+1][c],w-1);	
		if(c==2)ans[r][x-1][y][c]=min(ans[r][x-1][y][c],w-1);
		if(c==3)ans[r][x][y-1][c]=min(ans[r][x][y-1][c],w-1);			
	}
}
void turn(int r,int d){
	vector<wz>q;
	for(int x=1;x<=200;x++)
		for(int y=1;y<=200;y++)
			for(c=0;c<4;c++)
				if(ans[r][x][y][c]<=n and ans[r][x][y][c]>0){
					wz kk={x,y,c,ans[r][x][y][c]};
					q.emplace_back(kk);	}
	for(auto t:q){
		int x=t.x,y=t.y,c=t.c,w=t.w;	
		ans[r][x][y][(c+d)%4]=min(ans[r][x][y][(c+d)%4],w-1);
	}		
}
int main(){
	cin>>r;
	for(int i=1;i<=r;i++)
		for(int x=1;x<=200;x++)
			for(int y=1;y<=200;y++){
				for(c=0;c<4;c++)ans[i][x][y][c]=100;
			}
	for(int i=1;i<=r;i++){
		cin>>x>>y>>c>>n;
		x+=100,y+=100,c/=90;
		ans[i][x][y][c]=n;
		for(int k=1;k<=n;k++){
			char s;
			cin>>s;
			if(s=='S'){
				wd(i);
			}else {
				cin>>d;
				d/=90;
				turn(i,d);
			}
		}
	}
	for(int x=1;x<=200;x++)
		for(int y=1;y<=200;y++)
			for(int i=1;i<=r;i++){
				int kk=100;
				for(c=0;c<4;c++)kk=min(kk,ans[i][x][y][c]);
				if(kk>=100){dd[x][y]=-1;break;}
				dd[x][y]+=kk;
			}
	int mi=100,mx=0,my=0;
	for(int x=1;x<=200;x++){
		for(int y=1;y<=200;y++){
			if(dd[x][y]<=mi and dd[x][y]>=0 and dd[x][y]<100){
				mi=dd[x][y];
				mx=x-100,my=y-100;
			}
		}	
	}	
	if(mi==100)cout<<-1;
	else {
		cout<<mi<<endl;
		cout<<mx<<' '<<my;
	}
	return 0;
}
```

---

