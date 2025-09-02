# Kicker

## 题目描述

Kicker (table football) is a board game based on football, in which players control the footballers' figures mounted on rods by using bars to get the ball into the opponent's goal. When playing two on two, one player of each team controls the goalkeeper and the full-backs (plays defence), the other player controls the half-backs and forwards (plays attack).

Two teams of company Q decided to battle each other. Let's enumerate players from both teams by integers from $ 1 $ to $ 4 $ . The first and second player play in the first team, the third and the fourth one play in the second team. For each of the four players we know their game skills in defence and attack. The defence skill of the $ i $ -th player is $ a_{i} $ , the attack skill is $ b_{i} $ .

Before the game, the teams determine how they will play. First the players of the first team decide who will play in the attack, and who will play in the defence. Then the second team players do the same, based on the choice of their opponents.

We will define a team's defence as the defence skill of player of the team who plays defence. Similarly, a team's attack is the attack skill of the player of the team who plays attack. We assume that one team is guaranteed to beat the other one, if its defence is strictly greater than the opponent's attack and its attack is strictly greater than the opponent's defence.

The teams of company Q know each other's strengths and therefore arrange their teams optimally. Identify the team that is guaranteed to win (if both teams act optimally) or tell that there is no such team.

## 说明/提示

Let consider the first test sample. The first team can definitely win if it will choose the following arrangement: the first player plays attack, the second player plays defence.

Consider the second sample. The order of the choosing roles for players makes sense in this sample. As the members of the first team choose first, the members of the second team can beat them (because they know the exact defence value and attack value of the first team).

## 样例 #1

### 输入

```
1 100
100 1
99 99
99 99
```

### 输出

```
Team 1
```

## 样例 #2

### 输入

```
1 1
2 2
3 3
2 2
```

### 输出

```
Team 2
```

## 样例 #3

### 输入

```
3 3
2 2
1 1
2 2
```

### 输出

```
Draw
```

# 题解

## 作者：_Execution_ (赞：1)

## 思路

由于只有四个人，所以可以直接判断。

如果一个人攻击值大于对面任意一个人的防守值，且另一个人的防守值大于对面任意一个人的攻击值，那么这个队就必胜。

如果两队都不能必胜，那么输出 ``Draw`` 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2],b[2],c[2],d[2];
int main(){
  cin>>a[0]>>a[1]>>b[0]>>b[1]>>c[0]>>c[1]>>d[0]>>d[1];
  if((a[0]>c[1]&&a[0]>d[1]&&b[1]>c[0]&&b[1]>d[0])||(b[0]>c[1]&&b[0]>d[1]&&a[1]>c[0]&&a[1]>d[0])){
    cout<<"Team 1";
	  return 0;  
  }
  if((c[1]>a[0]&&d[0]>b[1]||d[1]>a[0]&&c[0]>b[1])&&(c[1]>b[0]&&d[0]>a[1]||d[1]>b[0]&&c[0]>a[1])){
    cout<<"Team 2";
	  return 0;  
  }
  cout<<"Draw";
  return 0;
}
```


---

## 作者：nydzsf_qwq (赞：1)

## CF411C

若第 $1$ 队能赢，说明存在一种方式使得第 $2$ 队不管怎么选第 $1$ 队都能赢

所以有一个人的防守值比第 $2$ 队两个人的攻击值都大，且另一个人的攻击值比第 $2$ 队两个人的防守值都大

若第 $2$ 队能赢，说明不管第一队怎么选，第二队都有一种方案能够赢第 $1$ 队

类似第一种情况判断即可

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a1,a2,b1,b2,c1,c2,d1,d2;
int main() {
	scanf("%d%d%d%d%d%d%d%d",&a1,&a2,&b1,&b2,&c1,&c2,&d1,&d2);
	if(a1>max(c2,d2)&&b2>max(c1,d1)||a2>max(c1,d1)&&b1>max(c2,d2)) printf("Team 1\n");
	else if((c2>a1&&d1>b2||d2>a1&&c1>b2)&&(c2>b1&&d1>a2||d2>b1&&c1>a2)) printf("Team 2\n");
	else printf("Draw\n");
	return 0;
}
```

---

## 作者：Brute_Force (赞：0)

### 思路
本题可以采用分支来写。

首先，此题说的是**必胜**，说明必定要使其中一队的一人的攻击值大于另一队四人中最大的一个防守值，同理，这一队必定要满足其中一人的防守值大于另一队四人中最大的的攻击值，否则无法百分百取胜。

### 代码
本题为了方便阅读代码，所以在两个大条件内增加了换行和空格。
```cpp
#include<iostream>
using namespace std;
int main()
{
	int a1,a2,b1,b2;
	int c1,c2,d1,d2;
    cin>>a1>>a2>>b1>>b2;
    cin>>c1>>c2>>d1>>d2;
    if
	(
	  (a1>c2&&a1>d2&&b2>c1&&b2>d1)||
	  (b1>c2&&b1>d2&&a2>c1&&a2>d1)
	)
	{
        cout<<"Team 1";
    }
    else if
	(
	  (c2>a1&&d1>b2||d2>a1&&c1>b2)&&
	  (c2>b1&&d1>a2||d2>b1&&c1>a2)
	)
	{
        cout<<"Team 2";
    }
    else cout<<"Draw";
    return 0;
}
```

---

## 作者：zqh123b (赞：0)

[luogu 传送门](https://www.luogu.com.cn/problem/CF411C)  
[CF 传送门](https://codeforces.com/problemset/problem/411/C)  

----

### 【题目描述】  
两队各两人进行比赛，一人进攻，一人防守。若其中一队攻破了对方的防守并且防守成功，即可获胜。  
第一队先确定攻防人员，第二队可以根据第一队确定的确定己方的攻防人员。

----

### 【题目分析】  

#### 【误区】  
双方的获胜条件是否一样？**不一样！**  

第一队需要在对方无论怎么排兵布阵的情况下都满足获胜要求。  
但第二队知道第一队的攻防人员，更容易获胜。 

----

#### 【比赛情况】
主要有以下几种情况：

1. 一号选手的攻击力比三四号选手的防御力都高，且二号选手的防御力比三四号选手的攻击力都高：**一队获胜**  
2. 二号选手的攻击力比三四号选手的防御力都高，且一号选手的防御力比三四号选手的攻击力都高：**一队获胜**

以上为一队的必胜条件。

3. 三号选手的防御力比一号选手的攻击力高，且四号选手的攻击力比二号选手的防御力高。  
4. 四号选手的防御力比一号选手的攻击力高，且三号选手的攻击力比二号选手的防御力高。  
5. 三号选手的防御力比二号选手的攻击力高，且四号选手的攻击力比一号选手的防御力高。  
6. 四号选手的防御力比二号选手的攻击力高，且三号选手的攻击力比一号选手的防御力高。  

~~可能有些拗口啊。。。~~  

但以上的四种情况并不是满足其中一条二队就可以获胜，而是三四条中要至少满足一条，且五六条中要至少满足一条。

----

#### 【总结方法】  

##### 【判断一队获胜】
```cpp
a1>max(c2,d2)&&b2>max(c1,d1)||a2>max(c1,d1)&&b1>max(c2,d2)
```

##### 【判断二队获胜】
```cpp
(c2>a1&&d1>b2||d2>a1&&c1>b2)&&(c2>b1&&d1>a2||d2>b1&&c1>a2)
```

----

### 【代码实现】
```cpp
#include<bits/stdc++.h>
using namespace std;
int a1,a2;
int b1,b2;
int c1,c2;
int d1,d2;
int main(){
	cin>>a1>>a2;
	cin>>b1>>b2;
	cin>>c1>>c2;
	cin>>d1>>d2;
	if(a1>max(c2,d2)&&b2>max(c1,d1)||a2>max(c1,d1)&&b1>max(c2,d2)){
		cout<<"Team 1"<<endl; 
	}else if((c2>a1&&d1>b2||d2>a1&&c1>b2)&&(c2>b1&&d1>a2||d2>b1&&c1>a2)){
		cout<<"Team 2"<<endl;
	}else{
		cout<<"Draw"<<endl;
	}
	return 0;
}
```


---

## 作者：Rookie_t (赞：0)

第一种情况，如果一队的进攻队员的攻击值比二队任何一位队员的防守值都大，且一队的防守队员的防守值比二队任何一位队员的攻击值都大，那么肯定是一队有必胜策略。 

第二种情况，如果二队的进攻队员的攻击值比一队任何一位队员的防守值都大，
且二队的防守队员的防守值比一队任何一位队员的攻击值都大，那么肯定是二队有必胜策略。

如果两队都没有必胜策略，那就输出  $\texttt{draw}$。 

下面贴代码： 

```cpp
#include<bits/stdc++.h>
using namespace std;
int a1,a2,b1,b2,c1,c2,d1,d2;
int main(){
	ios::sync_with_stdio(false);
	cin>>a1>>a2>>b1>>b2>>c1>>c2>>d1>>d2;
	if(a1>max(c2,d2)&&b2>max(c1,d1)||a2>max(c1,d1)&&b1>max(c2,d2)){//第一种情况 
		cout<<"Team 1"<<endl; 
	}
	else if((c2>a1&&d1>b2||d2>a1&&c1>b2)&&(c2>b1&&d1>a2||d2>b1&&c1>a2)){//第二种情况
		cout<<"Team 2"<<endl;
	}
	else{//两队都没有必胜策略的情况 
		cout<<"Draw"<<endl;
	}
	return 0;
}
```


---

## 作者：JacoAquamarine (赞：0)

一道超级水的思维题，又是exlg跳题跳到的，建议评红。

### 思路

分类讨论的思维题

如果一队有必胜策略，则二队无论如何布置阵形都无法打败一队，则一队必须有一个人攻击值比二队两个人都大，另外一个人防守值比二队两个人防守值都大。

```cpp
if(a1>c2&&a1>d2&&b2>c1&&b2>d1||a2>c1&&a2>d1&&b1>c2&&b1>d2)cout<<"Team 1\n";
```

如果二队有必胜策略，则一队无论如何布置阵形都无法打败二队。

```cpp
if((c2>b1&&d1>a2||d2>b1&&c1>a2)&&(c2>a1&&d1>b2||d2>a1&&c1>b2))cout<<"Team 2\n";
```

其余的输出 `Draw`。

---

## 作者：xwh_hh (赞：0)

这道题建议评橙。  
这其实挺水的，一共只有 $2^2=4$ 种情况，直接暴力枚举就行了。具体见代码注释。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5],b[5];
int check(int c1,int c2){//判断第一队胜负状态，c1、c2是进攻选手编号 
	int A1=a[c1],B1=b[3-c1],A2=a[c2],B2=b[7-c2];
	if(A1>B2&&A2<B1) return 1;//胜 
	if(A1<B2&&A2>B1) return -1;//负 
	return 0;
}
int main(){
	cin>>a[1]>>b[1]>>a[2]>>b[2]>>a[3]>>b[3]>>a[4]>>b[4];
	int x1=check(1,3),x2=check(1,4),x3=check(2,3),x4=check(2,4);//存放每种情形胜负状态
	if((x1>0&&x2>0/*1号进攻可胜*/)||(x3>0&&x4>0/*2号进攻可胜*/)) cout<<"Team 1";
	else if((x1<0||x2<0/*1号进攻可被打败*/)&&(x3<0||x4<0/*2号进攻也可被打败*/)) cout<<"Team 2";
	else cout<<"Draw";
	return 0;
}
```

---

## 作者：wangkangyou (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF411C)

题意已经很简洁了，分类讨论即可.

如果 $A$ 队一定能赢，那么我们经过推论可以得出，$A$ 队一定有一队组合可以使无论 $B$ 队怎么排兵布阵都可以在两方面保持彻底的优势击败 $B$ 队。举个栗子吧：

假设四个人的进攻 $(a)$ 和防守 $(b)$ 值如下：

$a = \{100,-1,0,0\}$

$b = \{-1,100,0,0\}$

我们可以发现，尽管 1 号队员的防守值是最低的，但 TA 的进攻值非常高，打进攻位非常合适；而 2 号队员的防守也很稳，非常适合防守。于是尽管 1 号防守 2 号进攻的安排一定会输，但并不妨碍 $A$ 队改变战术来应对敌方的任何安排而取得胜利。

而我们看看 $B$ 队一定胜利的可能性。由于 $B$ 队的选择在 $A$ 之后，局势就对 $B$ 有利了，只要 $B$ 有能应对 $A$ 的所有办法，那么胜利者就为 $B$ 队了。

如果以上两种情况都没有发生，胜券就不在任何队伍手里了，输出平局。

上代码：(个人觉得直接判断较麻烦，用循环简化了一下)
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read (){
	int sum = 0, f = 1;
	char ch = getchar ();
	for (;!isdigit (ch); ch = getchar ()) if (ch == '-') f = -1;
	for (;isdigit (ch); ch = getchar ()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return sum * f; 
}
void write (int x){
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar ('0' + x % 10);
	return; 
}
const int N = 1e6 + 10;
int a[N], b[N]; 
signed main (){
	for (int i = 1; i <= 4; ++ i){
		a[i] = read ();
		b[i] = read ();
	}
	for (int i = 1; i <= 2; ++ i){
		if (a[i] > b[3] && a[i] > b[4] && b[3 - i] > a[3] && b[3 - i] > a[4]){
			puts("Team 1");
			return 0;
		}
	}
	if ((b[3]>a[1]&&a[4]>b[2]||b[4]>a[1]&&a[3]>b[2]) && (b[3]>a[2]&&a[4]>b[1]||b[4]>a[2]&&a[3]>b[1])){
		puts("Team 2");
		return 0;
	}
	bool flag = 1;
	for (int i = 1; i <= 2; ++ i){
		bool f = 0;
		for (int j = 3; j <= 4; ++ j){
			if (b[j] > a[i] && a[7 - j] > b[3 - i]){
				f = 1;
			}
		}
		if (!f) flag = 0;
	} 
	if (flag){
		puts("Team 2");
		return 0;
	}
	puts("Draw");
	return 0;
}
```

---

## 作者：_easy_ (赞：0)

# 思路
思维题，只需要分类讨论就行了。
1. 当第 $1$ 队赢时，必须满足有一对组合能碾压对面的攻防手。
代码如下：
```cpp
if(a>f&&a>h&&d>e&&d>g){
	cout<<"Team 1";
	return 0;
}//第一对
if(b>e&&b>g&&c>f&&c>h){
	cout<<"Team 1";
	return 0;
}//第二对
```
2. 当第 $2$ 队赢时，必须满足对面不管选什么都要有可以碾压对面的组合。
代码如下：
```cpp
if(((e>d&&h>a)||(f>a&&g>d))&&((e>b&&h>c)||(f>c&&g>b))){
		cout<<"Team 2";
		return 0;
	}
```
3. 其余情况输出 $\texttt{Draw}$。
# 代码
AC代码已经分段给出。

---

