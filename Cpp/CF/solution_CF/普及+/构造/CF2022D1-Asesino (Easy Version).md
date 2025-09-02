# Asesino (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, you can ask at most $ n+69 $ questions. You can make hacks only if both versions of the problem are solved.

This is an interactive problem.

It is a tradition in Mexico's national IOI trainings to play the game "Asesino", which is similar to "Among Us" or "Mafia".

Today, $ n $ players, numbered from $ 1 $ to $ n $ , will play "Asesino" with the following three roles:

- Knight: a Knight is someone who always tells the truth.
- Knave: a Knave is someone who always lies.
- Impostor: an Impostor is someone everybody thinks is a Knight, but is secretly a Knave.

Each player will be assigned a role in the game. There will be exactly one Impostor but there can be any (possible zero) number of Knights and Knaves.

As the game moderator, you have accidentally forgotten the roles of everyone, but you need to determine the player who is the Impostor.

To determine the Impostor, you will ask some questions. In each question, you will pick two players $ i $ and $ j $ ( $ 1 \leq i, j \leq n $ ; $ i \neq j $ ) and ask if player $ i $ thinks that player $ j $ is a Knight. The results of the question is shown in the table below.

 KnightKnaveImpostorKnightYesNoYesKnaveNoYesNoImpostorNoYes— The response of the cell in row $ a $ and column $ b $ is the result of asking a question when $ i $ has role $ a $ and $ j $ has row $ b $ . For example, the "Yes" in the top right cell belongs to row "Knight" and column "Impostor", so it is the response when $ i $ is a Knight and $ j $ is an Impostor.Find the Impostor in at most $ n + 69 $ questions.

Note: the grader is adaptive: the roles of the players are not fixed in the beginning and may change depending on your questions. However, it is guaranteed that there exists an assignment of roles that is consistent with all previously asked questions under the constraints of this problem.

## 说明/提示

Note that the example test cases do not represent an optimal strategy for asking questions and are only shown for the sake of demonstrating the interaction format. Specifically, we cannot determine which player is the Impostor from the questions asked in the examples.

In the first test case of the example, players at indices $ 2 $ and $ 6 $ are Knights, players at indices $ 1 $ , $ 3 $ , $ 5 $ , and $ 7 $ are Knaves, and the Impostor is at index $ 4 $ . The following is an explanation of the questions asked:

- In the first query, player $ i $ is a Knave and player $ j $ is a Knave. The answer is "yes" since Knaves always lie.
- In the second query, player $ i $ is a Knave and player $ j $ is a Knight. The answer is "no" since Knaves always lie.
- In the third query, player $ i $ is a Knight and player $ j $ is a Knave. The answer is "no" since Knights always tell the truth.
- In the fourth query, player $ i $ is a Knight and player $ j $ is a Knight. The answer is "yes" since Knights always tell the truth.
- In the fifth query, player $ i $ is a Impostor and player $ j $ is a Knave. The answer is "yes" since the Impostor always lies.
- In the sixth query, player $ i $ is a Impostor and player $ j $ is a Knight. The answer is "no" since the Impostor always lies.
- In the seventh query, player $ i $ is a Knave and player $ j $ is a Impostor. The answer is "no" since Knaves always lie and Knaves thinks that the Impostor is a Knight.
- In the eighth query, player $ i $ is a Knight and player $ j $ is a Impostor. The answer is "yes" since Knights always tell the truth and Knights think that the Impostor is a Knight.

## 样例 #1

### 输入

```
2
7

1

0

0

1

1

0

0

1

4

0

1

1

1```

### 输出

```
? 1 3

? 7 6

? 2 5

? 6 2

? 4 5

? 4 6

? 1 4

? 2 4

! 4

? 1 2

? 2 3

? 3 4

? 4 1

! 3```

# 题解

## 作者：ykzzldz (赞：2)

本文中，用 $(i,j)$ 表示一次询问的结果。显然，若 $(i,j)\ne(j,i)$，则 $i$ 和 $j$ 中必定有一个冒名顶替者。随后，我们只需要花费 $2$ 次操作询问 $(k,i)$ 和 $(i,k)$，其中，$k$ 为异于 $i$ 和 $j$ 的另一个人，若 $(i,k)\ne(k,i)$，冒名顶替者为 $i$，否则冒名顶替者为 $j$，总花费次数为 $n+2$。

---

## 作者：WuMin4 (赞：2)

## [CF2022D1 Asesino](https://codeforces.com/problemset/problem/2022/D1)

## 题意

交互题，有 $n$ 个人，其中有一些好人和一些坏人，还有一个内鬼，你每次可以选择问一个人回答另一个人是不是好人，回答如下表：

||好人|坏人|内鬼|
|---|---|---|---|
|好人|Yes|No|Yes|
|坏人|No|Yes|No|
|内鬼|No|Yes|-|

例如，你问内鬼一个好人是不是好人，他会回答 `No`。

你需要通过最多 $(n+69)$ 次询问找出内鬼。

## 思路

很显然，内鬼对另一人和另一人对内鬼的回答是相反的，而好人和坏人之间的回答是相同的，所以可以通过每次互相问两个人找出有内鬼嫌疑的两个人，再通过 $2$ 次额外的询问找出内鬼，询问次数最大为 $(n+2)$ 次，可以通过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		string res1,res2;
		int id=0;
		for(int i=1;i<=n-(n%2);i+=2){
			cout<<"? "<<i<<" "<<i+1<<endl;
			cin>>res1;
			cout<<"? "<<i+1<<" "<<i<<endl;
			cin>>res2;
			if(res1!=res2){
				id=i;
				break;
			}
		}
		if(!id){
			cout<<"! "<<n<<endl;
			continue;
		}
		else{
			if(id==1){
				cout<<"? "<<id+1<<" "<<id+2<<endl;
				cin>>res1;
				cout<<"? "<<id+2<<" "<<id+1<<endl;
				cin>>res2;
				if(res1==res2)
					cout<<"! "<<id<<endl;
				else
					cout<<"! "<<id+1<<endl;
			}
			else{
				cout<<"? "<<id-1<<" "<<id<<endl;
				cin>>res1;
				cout<<"? "<<id<<" "<<id-1<<endl;
				cin>>res2;
				if(res1==res2)
					cout<<"! "<<id+1<<endl;
				else
					cout<<"! "<<id<<endl;
			}
		}
	}
	return 0;
}
```

---

## 作者：WYX1210 (赞：1)

## 思路
用 $(i,j)$ 表示询问玩家 $i$ 是否认为玩家 $j$ 是骑士。\
从题目中的表格可以看出，当 $(i,j) ≠ (j,i)$ 时，$i$ 和 $j$ 中必有一个是冒名顶替者，所以找一个不是冒名顶替者的人 $k$ ，若 $(i,k) ≠ (k,i)$ 那么 $i$ 是冒名顶替者，否则 $j$ 是。\
所以直接遍历一遍即可，最多询问次数为 $n+2$。
## 代码
```cpp
#include<bits/stdc++.h>
#define maxn 200005
#define multicase() int t;cin>>t;while(t--)
using namespace std;
int n,a[maxn],b[maxn],x,y;
void solve()
{
	cin >> n ;
	bool flg = 0;
	for(int i=1;i<=n/2;i++)
	{
		cout << "? " << i*2-1 << " " << i*2 << endl;
		cin >> x;
		cout << "? " << i*2 << " " << i*2-1 << endl;
		cin >> y ;
		if(x!=y)
		{
			if(i>1)
			{
				cout << "? " << i*2-1 << " " << i*2-2 << endl;
				cin >> x;
				cout << "? " << i*2-2 << " " << i*2-1 << endl;
				cin >> y ;
			}
			else
			{
				cout << "? " << i*2-1 << " " << n << endl;
				cin >> x ;
				cout << "? " << n << " " << i*2-1 << endl;
				cin >> y;
			}
			if(x != y) cout << "! " << i*2-1 << endl;
			else cout << "! " << i*2 << endl;
			flg = 1;
			break;
		}
	}
	if(!flg) cout << "! " << n << endl;
}
int main()
{
	int t;
	cin >> t ;
	while(t--) solve(); 
	return 0;
}
```

---

## 作者：yifu_chen (赞：0)

#### 题目描述

交互题：有骑士、骗子、冒名顶替者三种角色。骑士说真话，骗子说假话，冒名顶替者说假话但是别人认为他是骑士。你可以提出 $n+69$ 个问题，问 $i$ 认为 $j$ 是否是骑士。问题的结果如下：

|            | 骑士  | 骗子  | 冒名顶替者 |
| ---------- | ----- | ----- | ---------- |
| 骑士       | `Yes` | `No`  | `Yes`      |
| 骗子       | `No`  | `Yes` | `No`       |
| 冒名顶替者 | `No`  | `Yes` | —          |

只有一名冒名顶替者，你需要回答他是谁。

#### 思路

通过观察表格的对称性可以发现，如果 $i,j$ 中有一个是冒名顶替者，则 $f(i,j)$ 与 $f(j,i)$ 结果不同。可以将 $n$ 个人两两配对相互提问，结果不同的那一组中有一个是冒名顶替者。然后再选择另一个人，与这一组中的一个人相互提问。同样地，如果结果不同则冒名顶替者就是选定的这个人，否则是另一个人。这样最劣情况下共提问 $n+2$ 次。

#### 参考代码

```CPP
#include<bits/stdc++.h>
using namespace std;
int t,n;
bool opt;
bool ask(int a,int b)
{
	cout<<"? "<<a<<" "<<b<<endl;
	cin>>opt;
	return opt;
}
void ans(int a)
{
	cout<<"! "<<a<<endl;
	return;
}
void check(int a,int b)
{
	int c;
	if(a!=1&&b!=1)c=1;
	else if(a!=2&&b!=2)c=2;
	else if(a!=3&&b!=3)c=3;
	if(ask(a,c)!=ask(c,a))ans(a);
	else                  ans(b);
	return;
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		bool flag=false;
		for(int i=1;i<n-i+1;i++)
		{
			if(ask(i,n-i+1)!=ask(n-i+1,i))
			{
				check(i,n-i+1);
				flag=true;
				break;
			}
		}
		if(flag)continue;
		ans((n+1)/2);
	}
	return 0;
}
```

---

