# Sagheer and Crossroads

## 题目描述

Sagheer is walking in the street when he comes to an intersection of two roads. Each road can be represented as two parts where each part has $ 3 $ lanes getting into the intersection (one for each direction) and $ 3 $ lanes getting out of the intersection, so we have $ 4 $ parts in total. Each part has $ 4 $ lights, one for each lane getting into the intersection ( $ l $ — left, $ s $ — straight, $ r $ — right) and a light $ p $ for a pedestrian crossing.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF812A/a08cde5c54e404c978bae7b092917e8befa50c5b.png)An accident is possible if a car can hit a pedestrian. This can happen if the light of a pedestrian crossing of some part and the light of a lane that can get to or from that same part are green at the same time.

Now, Sagheer is monitoring the configuration of the traffic lights. Your task is to help him detect whether an accident is possible.

## 说明/提示

In the first example, some accidents are possible because cars of part $ 1 $ can hit pedestrians of parts $ 1 $ and $ 4 $ . Also, cars of parts $ 2 $ and $ 3 $ can hit pedestrians of part $ 4 $ .

In the second example, no car can pass the pedestrian crossing of part $ 4 $ which is the only green pedestrian light. So, no accident can occur.

## 样例 #1

### 输入

```
1 0 0 1
0 1 0 0
0 0 1 0
0 0 0 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
0 1 1 0
1 0 1 0
1 1 0 0
0 0 0 1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
1 0 0 0
0 0 0 1
0 0 0 0
1 0 1 0
```

### 输出

```
NO
```

# 题解

## 作者：HUANGRUI11 (赞：1)

感觉题目有点抽象，主要是题目翻译太过简略，所以我特意来给大家翻译一下。

输入一共有四行，每行四个数：$l_i,s_i,r_i,p_i$。
$l$ 代表左转，$s$ 代表直走，$r$ 代表右转，而 $p$ 代表的是人行道（因为这个卡了十分钟）。

很明显，如果在人行道是绿灯时，即 $p_i$ 为 $1$ 时，如果
 $l_i,s_i,r_i$ 任一为 $1$，都会出现事故。而且如果对面的 $s_i$ 为 $1$，左边的 $r_i$ 为 $1$，右边的 $l_i$ 为
 $1$，都可能发生事故。以此进行判断解题。

 另外建议管理员将本题降橙，代码就不展示了。

---

## 作者：_Execution_ (赞：1)

## 思路
若一条人行道可以通过，则该路段所有方向，对面路段直行，左侧路段右转，右侧路段左转，这六个方向有车通过就会出事。

枚举判断，只要人行道有人过并且以上情况中任何一种存在，即会出事；否则就不会出事。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
bool l[4], s[4], r[4], p[4];
int main() {
  for (int i = 0; i < 4; i++) {
    cin >> l[i] >> s[i] >> r[i] >> p[i];
  }
  for (int i = 0; i < 4; i++) {
    if (p[i]) {
      if ((l[i] || s[i] || r[i] || r[(i + 3) % 4] || s[(i + 2) % 4] || l[(i + 1) % 4])) {
        puts("YES");
        return 0;
      }
    }
  }
  cout << "NO";
  return 0;
}
```

---

## 作者：Eason_AC (赞：1)

## Content
有一个十字路口，从最下面的部分开始，逆时针依次标号为 $1,2,3,4$。每个部分有四个灯，分别为左转的灯、直行的灯、右转的灯以及人行通道灯（只有可能为红灯和绿灯）。如果某个部分的人行横道的灯光和可以到达或离开该部分的车道的灯光同时为绿灯，则可能会发生交通事故。现在，给出四个部分的 $16$ 个灯的情况（$0$ 表示红灯、$1$ 表示绿灯），请你预测是否会发生交通事故。
## Solution
直接暴力判断情况即可，只不过判断的条件有些多罢了。

这里借用一下题面的图来详细讲解：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF812A/a08cde5c54e404c978bae7b092917e8befa50c5b.png)

我们可以很容易地发现，只要人行横道灯是绿色，并且在这个部分中左转、直行、右转的灯中有一个灯亮绿灯，那么就会发生交通事故。

当然，除了上面这些以外，还有一些情况也会发生交通事故：

1. $1$ 号部分的人行横道灯亮绿灯，并且 $2$ 号部分的左转灯、$3$ 号部分的直行灯、$4$ 号部分的右转灯中有一个灯亮绿灯。
2. $2$ 号部分的人行横道灯亮绿灯，并且 $1$ 号部分的右转灯、$3$ 号部分的左转灯、$4$ 号部分的直行灯中有一个灯亮绿灯。
3. $3$ 号部分的人行横道灯亮绿灯，并且 $1$ 号部分的直行灯、$2$ 号部分的右转灯、$4$ 号部分的左转灯中有一个灯亮绿灯。
4. $4$ 号部分的人行横道灯亮绿灯，并且 $1$ 号部分的左转灯、$2$ 号部分的直行灯、$3$ 号部分的右转灯中有一个灯亮绿灯。

上面这些都用一个 $\texttt{if}$ 来判断就好。条件很多，需要细心和耐心。
## Code
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int l[7], r[7], s[7], p[7];

int main() {
	for(int i = 1; i <= 4; ++i)	scanf("%d%d%d%d", &l[i], &s[i], &r[i], &p[i]);
	if((p[1] && (l[1] || s[1] || r[1] || l[2] || s[3] || r[4])) || (p[2] && (r[1] || l[2] || s[2] || r[2] || l[3] || s[4])) || (p[3] && (s[1] || r[2] || l[3] || s[3] || r[3] || l[4])) || (p[4] && (l[1] || s[2] || r[3] || l[4] || s[4] || r[4])))	printf("YES");
	else	printf("NO");
	return 0;
}
```

---

## 作者：EasyCM (赞：0)

### 题目大意：
输入一共有四行，每行四个数：分别为 $l_i$，$r_i$，$s_i$，$p_i$；分别代表左转，右转，直行，人行道；要判断出是否会发生事故。
***
### 解题思路：
仔细想一想可以发现，当 $p_i$ 为 $1$ 时，只要 $l_i$，$r_i$，$s_i$ 其中之一为 $1$ 时，就会发生事故；还有当对面的 $s_i$ 为 $1$，左边的 $r_i$ 为 $1$ 时，右边的 $l_i$ 为 $1$ 时，也可能发生事故。所以只要判断上面两个条件是否成立一个，如果成立就是 `YES` 否则就为 `NO`。
***
### Code：
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e2;
long long l[N],r[N],s[N],p[N];
int main() 
{
	for(int i=1;i<=4;i++)	
    cin>>l[i]>>r[i]>>s[i]>>p[i];
	if((p[1]&&(l[1]||s[1]||r[1]||l[2]||s[3]||r[4]))||(p[2] &&(r[1]||l[2]||s[2]||r[2]||l[3]||s[4]))||(p[3]&&(s[1]||r[2]||l[3]||s[3]||r[3]||l[4]))||(p[4]&&(l[1]||s[2]||r[3]||l[4]||s[4]||r[4])))	
	cout<<"YES";
	else	
	cout<<"NO";		
 	return 0;
}
```
感谢你的阅读！

---

## 作者：huangjunhan (赞：0)

# 题目大意
给你一个十字路口，四个方向依次标为 1、2、3、4，现在给出这 4 个红绿灯的 16 个方向，如果人看到的和车看到的都是绿灯，就会发生事故，问你在这个路口会不会发生事故。
# 解题思路
若一条人行道可以通过，则该路段的所有方向中，对面路段直行、左侧路段右转、右侧路段左转、这六个方向中有车通过就会发生事故。接下来，只要枚举不同情况，再依次判断后就能得出答案。
# 正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110],b[110],c[110],d[110];
int main(){
	for(int i=0;i<4;i++)scanf("%d%d%d%d",a+i,b+i,c+i,d+i);
	for(int i=0;i<4;i++){
		if(d[i]&&(a[i]||b[i]||c[i]||c[(i+3)%4]||b[(i+2)%4]||a[(i+1)%4])){
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
}

```

---

## 作者：jasonshen_ (赞：0)

## 题意
给您一个十字路口，四个方向依次标为 $1,2,3,4$，现在给出这 $4$ 个红绿灯的 $16$ 个方向，如果人看到的和车可以到达或离开该部分的车道的灯光看到的都是绿灯，就会发生事故，问：会不会发生事故。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int l[4],s[4],r[4],p[4];
	for (int i=0;i<4;i++)cin>>l[i]>>s[i]>>r[i]>>p[i];
	for (int i=0;i<4;i++)
	if (p[i]&&(l[i]||s[i]||r[i]||r[(i+3)%4]||s[(i+2)%4]||l[(i+1)%4]))
		return cout<<"YES",0;
	cout<<"NO";
}


```



---

## 作者：_Jonny_404 (赞：0)

题目翻译不是很严谨，这里给出准确翻译：

给您一个十字路口，四个方向依次标为 $1,2,3,4$，现在给出这 $4$ 个红绿灯的 $16$ 个方向，第 $i$ 个红绿灯的 $4$ 个方向为 $l_i,s_i,r_i,p_i$，分别表示这个路口向左转、直行、向右转和人行道的红绿灯的状况，`1` 表示红灯，`0` 表示绿灯。如果人看到的和车可以到达或离开该部分的车道的灯光看到的都是绿灯，就会发生事故，问：会不会发生事故。

首先来看题目里给出的图片：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF812A/a08cde5c54e404c978bae7b092917e8befa50c5b.png)

这幅图清晰地告诉我们，每个路口 $l_i,s_i,r_i,p_i$ 的路线。

再看我自己画的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/0zplkf6r.png)

我们不妨模拟一下，当图中的 $d_1$ 是可通行（即 $p_i=1$）时，会有哪些车道来的车会撞人：

1. $l_1,s_1,r_1$ 绿灯时的来车肯定会撞人；
2. $l_2$ 绿灯时的车左转来到道路 $1$，也会撞人；
3. $s_3$ 绿灯时的车直行来到道路 $1$，会撞人；
4. $r_4$ 绿灯时的车右转来到道路 $1$，也会撞人。

由此可推出当 $p_1$ 和 $l_1,s_1,r_1,l_2,s_3,r_4$ 同为绿灯时，会发生惨案。那么 $p_2,p_3,p_4$ 的绿灯会和哪些绿灯车道发生事故也可由此推出了，这里不再演示。

楼上两篇题解都是直接枚举 $4$ 个路口的状况，但是我直接用了两个 `for` 解决问题（其中一个输入）。具体核心代码：

```cpp
for(int i=1;i<=4;i++)
	if(p[i]&&(l[i]||s[i]||r[i]||l[(i==4)?1:(i+1)]||s[(i>=3)?(i+2-4):(i+2)]||r[(i!=1)?(i+3-4):4]))
		ans=1;
```

注：`if` 语句的条件中，后面三个下标可能会发生越界，所以用三目运算符先判断是否越界，然后如果越界的话就变为实际下标。

科普一下三目运算符的格式：

```cpp
(条件)?(条件成立情况下执行的代码):(条件不成立执行的代码)
```

最后奉上 AC 代码：

```cpp
#include<iostream>
using namespace std;

bool l[5],s[5],r[5],p[5];
bool ans;

int main()
{
	for(int i=1;i<=4;i++)
		cin>>l[i]>>s[i]>>r[i]>>p[i];
	for(int i=1;i<=4;i++)
		if(p[i]&&(l[i]||s[i]||r[i]||l[(i==4)?1:(i+1)]||s[(i>=3)?(i+2-4):(i+2)]||r[(i!=1)?(i+3-4):4]))
			ans=1;
	cout<<(ans?"YES":"NO")<<endl;
	return 0;
}
```

---

