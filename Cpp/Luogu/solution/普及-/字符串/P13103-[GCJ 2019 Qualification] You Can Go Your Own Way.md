# [GCJ 2019 Qualification] You Can Go Your Own Way

## 题目描述

你刚刚进入了世界上最简单的迷宫。你从一个 $N \times N$ 的单位方格的西北角单元格出发，目标是到达东南角单元格。你只能进行两种类型的移动：向东移动一格，或向南移动一格。你可以进入任意单元格，但不能移动出格子外。

你本以为自己是第一个解开这个迷宫的人，但你发现了脚印。你的对手 Labyrinth Lydia 已经按照上述规则走完了迷宫！

作为一个有创意的人，你不想重复 Lydia 的任何一步。具体来说，如果她的路径包含了从某个单元格 A 移动到相邻单元格 B 的一步，你的路径中不能包含从 A 到 B 的移动（但你可以访问 A 或 B，只要不是从 A 到 B）。请你找出一条满足条件的路径。

下图中，Lydia 的路径用蓝色表示，你的一种可行路径用橙色表示：

![](https://cdn.luogu.com.cn/upload/image_hosting/n9xdyxsk.png)

## 说明/提示

**样例解释**

样例 1 中，迷宫太小，你只剩下唯一一种合法解法。

样例 2 对应上图。注意，路径可以交叉。

**数据范围**

- $1 \leq T \leq 100$。
- $P$ 恰好包含 $N-1$ 个 E 和 $N-1$ 个 S。

**测试点 1（5 分，可见）**

- $2 \leq N \leq 10$。

**测试点 2（9 分，可见）**

- $2 \leq N \leq 1000$。

**测试点 3（10 分，隐藏）**

- 最多 10 个用例满足 $2 \leq N \leq 50000$。
- 其余用例满足 $2 \leq N \leq 10000$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
2
SE
5
EESSSESE```

### 输出

```
Case #1: ES
Case #2: SEEESSES```

# 题解

## 作者：__F__ (赞：6)

## 题目大意  
给定一个 $N\times N$ 单位方格网，要求从西北角的单元格出发，到达东南角的单元格。但是只能向东或向南移动。同时会给出 Lydia 的路径，要求自己的路径不能与 Lydia 的路径相同，最后输出自己的路径。  
## 思路分析  
从一个方格网的西北角走到东南角，方法有很多种。题目说我们的路径不能与 Lydia 的路径重复，但是可以访问 Lydia 之前访问过的单元格。那么既然这是一个 $N\times N$ 的正方形网格，是一个轴对称图形，那我们只需要走与 Lydia 相反的路径就可以了。 Lydia 向东走我们就向南走， Lydia 向南走我们就向东走。这样我们自己的路径就会和 Lydia 的路径组成一个轴对称图形，对称轴为西北角与东南角的对角线所在的直线上。既高效快捷又不会走与 Lydia 重复的路径。  
## 代码实现  
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
string s;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T; 
	for(int i=1;i<=T;i++){
		cin>>n;
		cin>>s;
		cout<<"Case #"<<i<<": ";
		for(int j=0;j<(n-1)*2;j++){
			if(s[j]=='S'){
				cout<<"E";
			}else{
				cout<<"S";
			}
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：yuhaotian000 (赞：5)

# 题解：P13103 [GCJ 2019 Qualification] You Can Go Your Own Way
好久没来写题解了，继续水一发。
## 题目大意
有一个 $N \times N$ 的迷宫，我们要从左上角走到右下角且只能向右或下走，并且这两种走法都只有 $N-1$ 个。输入时我们用字母来代替，每个字符要么是大写 E（表示向右），要么是大写 S（表示向下）。现在给出了 Lydia 的路线称为 $P$，他的规则和你的一模一样，要求走出一个和 Lydia 的路线的完全不同（没有重合路线）的路线称为 $Y$。
## 题目解法
这道题要求和 Lydia 的路线没有重合路线，那么我们可以轻易的想到一种解决方案，那就是与 Lydia 的路线完全取反。也就是说，他往下走我们就往右走，他往右走我们就往下走。这个解法看起来是正确的，接下来我来证明他的正确性。

首先，我们先来证明这个走法是有效的。由于 Lydia 的解法力肯定包含 $N-1$ 个向下走的以及 $N-1$ 个向右走的，那么我们的取反后也是这样的，所以路径有效。

接下来我们证明不重合。假设 $P$ 的第 $k$ 步是从 $(i,j)$ 到 $(i',j')$，分为两种情况：

* 如果是 E：$(i,j) → (i,j+1)$，则 $Y$ 的第 $k$ 步是 S：$(x,y) → (x+1,y)$，要使得 $Y$ 的第 $k$ 步也是 $(i,j) → (i,j+1)$，必须有 $(x,y)=(i,j)$ 且 $(x+1,y)=(i,j+1)$，即 $y=j$ 且 $x+1=i$ 且 $y=j+1$，矛盾。

* 如果是 S：$(i,j) → (i+1,j)$，则 $Y$ 的第 $k$ 步是 E：$(x,y) → (x,y+1)$，要使得 $Y$ 的第 $k$ 步也是 $(i,j) → (i+1,j)$，必须有 $(x,y)=(i,j)$ 且 $(x,y+1)=(i+1,j)$，即 $x=i$ 且 $y+1=j$ 且 $x=i+1$，矛盾。

我们通过了两个证明，发现都是矛盾的，因此两条路线不重合。

那么经过证明，我们的解法有效且不会与 Lydia 的解法重合。因此直接这样输出就行了。

提示：注意数据范围！！！

## AC code
```
#include <bits/stdc++.h>
using namespace std;
char a[100005]; // 注意!不是a[50005]!
int main(){
    int t;
    cin>>t;
    int s=1;
    while(t--){
        cout<<"Case #"<<s<<": ";
        s++;
        int n;
        cin>>n>>a;
        for(int i=0;i<strlen(a);i++){
            if(a[i]=='E'){
                cout<<"S";
            }else{
                cout<<"E";
            }
        }
        cout<<endl;
    }
}
```

---

## 作者：Solune (赞：1)

## 题意
在 $N × N$ 的方格网中，从西北角（左上角）到东南角（右下角）只能向东 (E) 或向南 (S) 移动，构造一条有效路径，要求不重复给定路径（**Lydia** 的路径）中的任何一步移动（即若 **Lydia** 从单元格 A 移动到相邻单元格 B，新路径不能有同样的从 A 到 B 的移动）。
## 思路
由题目可知，新路径要使在 **Lydia** 经过的任何方格中下一步移动方向与其不同，所以可以让新路径在 **Lydia** 路径中下一步移动方向与其相反，这样，新路径在经过相同单元格时，其移动方向必然与 **Lydia** 不同，例如下图：

![png](https://cdn.luogu.com.cn/upload/image_hosting/mla17045.png)

图中两条路径即使存在重合的单元格（即路径交叉处），在这些重合位置上的移动方向也恰好相反。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin >> t;
	for(int i = 1; i <= t; ++i){
		int n;
		string s;
		cin >> n >> s;
		cout << "Case #" << i << ": "; 
		for(int i = 0; i < s.size(); ++i)
			if(s[i] == 'S') cout << 'E';
			else cout << 'S';
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：Natural_Selection (赞：1)

# 题解：P13103 

[The Problem](https://www.luogu.com.cn/problem/P13103)

## 思路

  首先，我们看到这题里有 `Special Judge`，所以很明显，它不只有一个答案。那我们就往简单里想，手玩几组就可以发现，只要我们向和 **Lydia** 相反的反方向走就行了，像这样：
  ![picture](https://cdn.luogu.com.cn/upload/image_hosting/g30hn2d7.png)
  ~~画技不好，多多谅解~~

  有了思路，不出意外下面就是——

## [AC](https://www.luogu.com.cn/record/222927593) 代码

```cpp
#include<bits/stdc++.h>
#define TheEnd return 0
using namespace std;
int main(){
    int t;
    cin>>t;
    int k=0;
    while(t--){
        int n;
        cin>>n;
        printf("Case #%d: ",++k);//样例格式
        string str;
        cin>>str;
        for(int i=0;i<2*n-2;i++){//输出与 Lydia 相反的方向
            if(str[i]=='E') cout<<"S";
            else cout<<"E";
        }
        cout<<endl;//别忘了换行
    }
    TheEnd;
}
```
~~管理大大就让我过了吧~~

---

## 作者：huhengrui2013 (赞：1)

### 题解：P13103 [GCJ 2019 Qualification] You Can Go Your Own Way

[传送门](https://www.luogu.com.cn/problem/P13103)

### 思路：

对于 Lydia 的每一步，我们只需要跟他对着来就是一组合法的答案，即他往南，我往东；他往东，我往南。（这样既不会与他路线重复，且能抵达终点，因为地图是正方形，他往东和往南的次数必然一样，那么反过来，我往南和往东的次数也一样，那样一定能达到终点）。

### AC Code:
```cpp

#include<bits/stdc++.h>

using namespace std;

int main(){
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
        cout<<"Case #"<<i<<": ";//多组数据
        int n;
        cin>>n;
        string s;
        cin>>s;
        for(int j=0;j<s.size();j++) {//遍历+对着来
            if(s[j]=='S') cout<<'E';
            else cout<<'S';
        }
        cout<<endl;
    }
}
```

---

## 作者：Clouds_dream (赞：1)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13103)

### 题目分析
我们只需要与这个人反着走就行。  
即他向 `E`，我们就向 `S`。  
因为我们每一步的方向都与他相反，所以我们不会和他有相同的移动，也不会导致我们离开网格。因此，这个策略是可行的。

### 代码实现

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int qwq;

signed main()
{
	fst
	cin>>qwq;
	for(int t=1;t<=qwq;t++){
		int n;
		cin>>n;
		string s,ans="";
		cin>>s;
		for(auto c:s){
			if(c=='E')ans+='S';//E->S,S->E
			else ans+='E';
		}
		cout<<"Case #"<<t<<": "<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：llh2012 (赞：1)

### 思路
因为迷宫为正方形，所以向东和向南走步数相同。  
可想到当 Lydia 向南走一步，我们就向东走一步；Lydia 向东走一步，我们就向南走一步，也可到达终点，且绝不会走相同的路。  
易证：当两人都走到同一格时，走的步数相同，无论 Lydia 怎么走，我们均会走相反的道路，故永不会走相同的路。
### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
char a[100010];
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>n;
        memset(a,0,sizeof(char));//记得重置
        for(int j=1;j<=2*n-2;j++){
            cin>>a[j];
        }
        cout<<"Case #"<<i<<": ";
        for(int j=1;j<=2*n-2;j++){
            if(a[j]=='E')
              cout<<"S";
            else
              cout<<"E";//走相反的路
        }
        cout<<endl;
    }
}
```

---

## 作者：_ByTT_ (赞：1)

# 题解：P13103 [GCJ 2019 Qualification] You Can Go Your Own Way
### 题意
要求走过一个边长为 $N$ 的正方形，从左上角到达右下角，不能与题中给出的路线相重合，一条都不可以！

需注意答案格式为较为特殊，题面中有强调，其中的 $x$ 是当前数据是第几组，$y$ 是通过 $S,E$ 组成的字符串给出路线。$S$ 是往下走，$E$ 是往右走。
### 思路
因为是求任何一条可以走的路，所以我们只需要找到一条最好找的即可。

因为是正方形，那么需要的 $S,E$ 一样，那么与原路不同的就可以有如下规律。是原路往下，我往左，原路往左，我往下。路线自然不可能重复了，答案易得，易证。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int T;cin>>T;
	for(int qwq=1;qwq<=T;qwq++){
		int n,len;string s,ans;
		cin>>n>>s;len=2*n-2;
		for(int i=0;i<len;i++){
			if(s[i]=='S') ans+='E';
			else ans+='S';
		}
		cout<<"Case #"<<qwq<<": "<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：pour_demain (赞：0)

我们每一步都不能和 **Lydia** 相同，首先可以下意识想到的就是每一步都和 **Lydia** 相反。

接下来我们就需要证明这个方法的正确性。\
显而易见的，如果我们某一步和 **Lydia** 是一样的，那么在不考虑起点和终点的情况下，我们至少要满足移动方向和 **Lydia** 一致，而现在我们每一步都和 **Lydia** 移动方向不一致，明显不可能和 **Lydia** 有重叠的移动。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin >> T;
	int i = 1;
	while(T--){
		int n;
		cin >> n;
		string s;
		cin >> s;
		cout << "Case #" << i << ": ";
		n *= 2;
		n -= 2;
		for(int j = 0;j < n;j++){
			if(s[j] == 'S') cout << 'E';
			else cout << 'S';
		}
		cout << endl;
		i++;
	}
	return 0;
}
```

唯一需要注意的细节就是这道题的输出格式很奇怪，并且多测要记得换行！

---

## 作者：wuyouawa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13103)

### 思路

首先观察题目，我们发现，既然要创造出不同的路径，那肯定就要每一步都不同，那么也就是说，向东要改为向南，而向南要改为向东。

注意到这样做一定是正确的，因为向东和向南的次数是相同的，所以把一个向东改为向南，后续也会有一个向南改为向东，就抵消了。

注意输出的格式。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,b;
string s;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>n>>s;
		for(int j=0;j<s.size();j++)
		{
			if(s[j]=='E')  s[j]='S';
			else  s[j]='E';
		}
		cout<<"Case #"<<i<<": "<<s<<endl;
	}
	return 0;
} 
```

---

## 作者：Restart_Justin (赞：0)

## 正解
如果 Lydia 向东移动，我们就向南移动；如果 Lydia 向南移动，我们就向东移动。因为我们如果和 Lydia 不在同一个点，那么移动肯定是合法的，我们如果和 Lydia 在同一个点，那么因为我们和 Lydia 的移动方向不同，所以移动也是合法的。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n;
string p;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> T;
    for (int k = 1; k <= T; k++) {
        cin >> n >> p;
        cout << "Case #" << k << ": ";
        for (char v : p)
            cout << (v == 'S' ? 'E' : 'S');
        cout << "\n";
    }
}
```

---

## 作者：aishiteru_mitsu_ha (赞：0)

# 题意
给定测试用例数量 $T$，每一个测试用例给定一个数 $N$，表示迷宫尺寸为 $N\times N$，给定一个字符串 $P$，表示 **Lydia** 通过迷宫的路径，求不与其路径冲突的有效路径。
# 思路
既然要不与其路径冲突，并且 **Lydia** 的路径一定是有效路径，那么我们就跟 **Lydia** 反着来，她往东走，我就往南走，她往南走，我就往东走，这样在满足路径有效不与 **Lydia** 的路径冲突的同时，也可以满足输出的 $y$ 是一个由 $2N-2$ 个字符组成的字符串，即存储 **Lydia** 的路径，根据其第 $i$ 步的方向来决定我们这一步的方向，最后，记得输出 ```Case #x: y``` 就行了。
# Code
```cpp
#include<bits/stdc++.h>
#define N 200086
#define ll long long
#define iakioi cout<<"I AK IOI"<<endl
using namespace std;
int t,n;
char ch[N];
inline int read();
int main(){
	t=read();
	for(int p=1;p<=t;p++){
		n=read();
		for(int i=1;i<=2*n-2;i++){
			cin>>ch[i];							//存储路径 
		}
		cout<<"Case #"<<p<<": ";				//提前输出Case #x: ,注意":"后还有一个空格 
		for(int i=1;i<=2*n-2;i++){
			if(ch[i]=='S') cout<<'E';			//与Lydia走相反方向 
			else cout<<'S';
		}
		cout<<endl;								//最后换行 
	}
	return 0;
}
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') {x=x*10+ch-48;ch=getchar();}
	return x*f;
}

```

---

## 作者：_fallen_leaves_ (赞：0)

[P13103 [GCJ 2019 Qualification] You Can Go Your Own Way](https://www.luogu.com.cn/problem/P13103)

## 题意
有一个人走迷宫，走出了一种方式，题目要求我们找到一条没有与这种方式重叠的路径。

## 思路
题目中说会有 $n-1$ 个 $E$ 和 $n-1$ 个 $S$，所以 $E$ 与 $S$ 一样多，所以我们只需要他走 $E$，我们就走 $S$，他走 $S$，我们就走 $E$，这样一定能保证我们与他走的不一样。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int step=0; 
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		string s;
		cin>>n>>s;
		step++;
		cout<<"Case #"<<step<<": ";
		for(int i=0;i<s.size();i++)
			if(s[i]=='E') cout<<"S";
			else cout<<"E";
		cout<<"\n";
	}
	return 0;
}

```

---

