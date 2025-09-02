# [NEERC 2017] Easy Quest

## 题目描述

一位年轻的英雄开始了他的英雄生涯。聪明的巫师给他建议了一个简单的第一个任务。在这个任务中，我们的年轻英雄遇到了 $n$ 个魔法生物，按特定顺序排列。为了帮助年轻英雄，巫师给了他一个线索——一个包含 $n$ 个整数 $a_{i}$ 的列表。

如果 $a_{i}$ 是正数，那么第 $i$ 个魔法生物是仁慈的，并给我们的英雄一个类型为 $a_{i}$ 的魔法物品。英雄可以保留多个相同类型的物品。

如果 $a_i$ 是负数，那么第 $i$ 个魔法生物是邪恶的，为了打败它，年轻英雄需要一个类型为 $-a_{i}$ 的魔法物品。所有魔法物品都是易碎的，只能使用一次。

如果 $a_{i}$ 是零，那么第 $i$ 个生物是独角兽。它会给英雄他所要求的任何魔法物品，但只能给一个。

你的任务是帮助年轻英雄完成第一个任务，击败途中所有的敌人，或者说这是不可能的。

## 说明/提示

时间限制：3 秒，内存限制：512 MB。

spj 提供者：@[shenyouran](\/user\/137367)。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
10
1 0 -4 0 0 -1 -3 0 -1 -2
```

### 输出

```
Yes
4 1 3 2
```

## 样例 #2

### 输入

```
5
5 8 0 -6 -3
```

### 输出

```
No
```

## 样例 #3

### 输入

```
3
2 -2 -2
```

### 输出

```
No
```

# 题解

## 作者：Up_Xu (赞：4)

# 题意
若 $a_i$ 为正数，提供一个价值为 $a_i$ 的物品。

若 $a_i$ 为负数，消耗一个价值为 $a_i$ 的物品。

若 $a_i$ 为 $0$，选择一个价值随意的物品。

要求判断所有 $a_i$ 为负数时的操作能否完成。

# 思路
很简单，开桶来记录每次的提供与消耗。但是，$a_i$ 为 $0$ 时选择的物品会影响到后面 $a_i$ 为负数的情况。那么我们就可以换种思路：在 $a_i$ 为 $0$ 时先不取物品，到后面 $a_i$ 为负数时，价值为 $a_i$ 的物品不够了，我们再拿前面 $a_i$ 为 $0$ 时的操作来补救。本题就轻松解决了。

# 陷阱

有可能出现价值随意的物品多余的情况，随意输出即可，本蒟蒻输出的是 $1000$。

# 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,t,i,x,sum,f[1010],a[1010];
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>x;
		if(x>0)f[x]++;//为正数时价值为x的物品数量加一 
		else if(x<0){
			if(f[-x]>0)f[-x]--;//数量足够，就消耗掉一个 
			else{
				if(sum>0)a[++t]=-x,sum--;//拿前面价值随意的物品来补救 
				else{cout<<"No";return 0;}//救不了输出No 
			}
		}
		else sum++;//价值随意的物品个数加一 
	}
	cout<<"Yes\n";
	for(i=1;i<=t;i++)
		cout<<a[i]<<" "; 
	while(sum>0)cout<<"1000 ",sum--;
}
```

---

## 作者：lizhengdong (赞：4)

[原题传送门](https://www.luogu.com.cn/problem/P6956)

## 1.题目分析
题目意思很简单，简单概括一下：

按输入 $a[i]$ 顺序做以下操作：  
1. 当 $a[i]$ 为正，获得一个为 $a[i]$ 的物品。  
2. 当 $a[i]$ 为负，消耗一个为 $a[i]$ 的物品。  
3. 当 $a[i]$ 为 $0$，获得一个为任意的物品。

然后看一下数据 $1 \le n \le 1000$ 和 $1 \le a[i] \le 1000$ ，发现 $n$ 和 $a[i]$ 都特别小，立刻就能想到模拟，再加点计数和贪心。

## 2.解题思路
边输入边做，如果是正数，那就在计数数组里记录，为 $0$ 则用变量记录个数，为负则分三种情况：
* 当计数数组中有这个数，则直接消耗掉。
* 当前面还有 $0$，则用掉一个 $0$，用数组保存（只因最后要输出前还要输出 `Yes` ）。
* 直接输出 `No` 。

## 3.一些陷阱
当做完后还有多余的 $0$，则随意输出（下面程序，我选择输出 $1$）。

## 4.AC代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,x,s,t,f[1010],b[1010];
int main(){
	cin>>n;
	s=t=0;
	for(i=1;i<=n;i++){
		cin>>x;
		if(x>0)f[x]++;//数组记录
		else if(x==0)s++;//零的数量
		else{
			x=abs(x);
			if(f[x]>0)f[x]--;//如果有直接用
			else if(s>t)b[++t]=x;//有零用零，数组保存
			else{
				cout<<"No";
				return 0;
			}
		}
	}
	cout<<"Yes\n";
	for(i=1;i<=s;i++)
		if(b[i]!=0)cout<<b[i]<<" ";
		else cout<<1<<" ";
}
```

---

## 作者：IDNo1 (赞：4)

# 1. 题目大意

按特定顺序输入了 $n$ 个数，第 $i$ 个数对应 $a_i$。

当 $a_i$ 为正数时，第 $i$ 个数会给英雄提供一个为 $a_i$ 的库存。

当 $a_i$ 为负数时，第 $i$ 个数需要英雄消耗一个为 $-a_i$ 的库存。

当 $a_i$ 为 $0$ 时，第 $i$ 个数可以给英雄提供一个任意的库存。

# 2. 思路

提示：此题纯模拟。

## （一）准备：

开一个 `vector` 专门装库存。

## （二）过程：

情况1：遇到正数，把它放进库存。

情况2：发现是一个负数，如果库存里有现成的，那就用掉，否则寻找有没有可以提供任意值的库存，那么就使用，还没有的话，就表示不能通过，输出 
`
No!
`
 。

情况3：发现是 $0$ 并存入。

# 3. 坑点提要

有时候，库存不一定用完，但是也要输出。

负数输入后，要转成正数使用。

# 4. 代码

具体见注释。
```
#include <iostream>
#include <vector>
using namespace std;
int n, a[1001], sum, t, f;//sum：非伤害性生物
vector<int > s, ans;//s是库存，t是之前遇到的0生物，ans：如果可以的答案
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        if (a[i] >= 0)sum ++;
    }
    if (sum < n - sum) { //不行
        puts("No");
        return 0;
    }
    for (int i = 1; i <= n; i ++) {
        if (a[i] > 0) { //表示这里有一个提供定数值的生物
            s.push_back(a[i]);//存好
        } else if (a[i] == 0) { //表示可以提供任意值的生物
            ++ t, ++ f;
        } else { //会消耗你的生物
            a[i] = abs(a[i]);
            //cout << "now:" << a[i] << "\n";
            bool k = 0;
            for (int j = 0; j < s.size(); j ++) { //寻找是否有储备
                if (s[j] == -0x3f)continue;//用过

                if (s[j] == a[i]) { //有
                    s[j] = -0x3f;//标记为使用过
                    k = 1;//打得过
                    break;
                }
            }
            if (k)continue;//消耗后继续走
            else { //需要补给，没有库存了
                ans.push_back(a[i]);//存
                if (!t) { //没救啦
                    puts("No");//挂了
                    return 0;//退出
                }
                t --;//使用
            }
        }
        /*
        cout << "库存：";
        for (int j = 0; j < s.size(); j ++) {
            if (s[j] != -0x3f) {
                cout << s[j] << " ";
            }
        }
        cout << " 剩余__'0'生物__：";
        {
            cout << t << " ";
        }
        cout << "\n";
        */
    }
    cout << "Yes\n";//
    for (int i = 0; i < ans.size(); i ++) { //答案输出
        cout << ans[i] << " ";
    }
    for(int i = 1; i <= f - ans.size(); i++) cout << rand()%10 << '\n'; //剩下的可以输出任何数，因为不论如何都已经可以过了
    return 0;
}
```
注：由于是 SPJ，所以可以以任意顺序使用为 $0$ 的库存。
 
附：[题目传送门](https://www.luogu.com.cn/problem/P6956)。

---

## 作者：yeshubo_qwq (赞：1)

## Description

既然没有翻译，那我给一个比较完整的题意。

一个英雄进行了一次探索。在这次探索中，英雄按特定顺序遇到了 $n$ 个魔法生物，第 $i$ 个魔法生物对应 $a_i$。

当 $a_i$ 为正数时，第 $i$ 个魔法生物会给英雄提供一个为 $a_i$ 的魔法物品。

当 $a_i$ 为负数时，第 $i$ 个魔法生物需要英雄消耗一个为 $-a_i$ 的魔法物品。

当 $a_i$ 为 $0$ 时，第 $i$ 个魔法生物可以给英雄提供一个任意的魔法物品。

你需要回答英雄是否可以完成这次探索（经过所有魔法生物），如果可以，请回答 $a_i$ 为 $0$ 魔法生物应该为英雄提供哪种魔法物品。

## Solution

模拟英雄探索的过程，用计数统计各个魔法物品的数量。

具体的过程可以按照魔法生物的分类来做：

+ 当 $a_i$ 为正数时，对应的魔法物品数量 $+1$。

+ 当 $a_i$ 为 $0$ 时，存放可任意提供的魔法物品（即最后的答案）的数组增加一个位置。

+ 当 $a_i$ 为负数时，对应的魔法物品数量如果还有，则 $-1$，若无，则考虑用可任意提供的魔法物品补足，如果位置不够，报告无解。

## Code

说明：洛谷上的数据或者 SPJ 存在错误，评测结果有误，建议到 CF 上进行评测。

链接：[Link](https://codeforces.com/gym/101630/submit)，选择 `E - Easy Quest` 即可。

```cpp
#include <bits/stdc++.h>
inline void read(int &x){
	char c=getchar(); int F=1;
	while (!isdigit(c) && c!='-') c=getchar();
	if (c=='-') F=-1,x=0; else x=(c^48);
	c=getchar();
	while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	x*=F;
}
inline void write(int x){
	if (x>9) write(x/10);
	putchar (x%10+'0');
}
int n,x,cnt,tot,a[1005],b[1005];
int main(){
	read(n);
	for (register int i=1;i<=n;i++){
		read(x);
		if (x>0) a[x]++;
		else if (x==0) cnt++;
		else{
			x=-x;//注意对应消耗的魔法物品要取正数 
			if (a[x]>0) a[x]--;
			else{
				b[++tot]=x;
				if (tot>cnt) return putchar('N'),putchar('o'),0;//位置超出，即位置不够 
			}
		}
	}
	putchar('Y'),putchar('e'),putchar('s'),putchar('\n');
	for (register int i=1;i<=tot;i++) write(b[i]),putchar(' ');
	for (register int i=tot+1;i<=cnt;i++) putchar('1'),putchar(' ');//注意：最后空的位置不可以输出0，因为没有为0的魔法物品
	return 0;
}
```


---

## 作者：Misophiliac (赞：0)

### 前言

比较简单的贪心，码量也不大，感觉黄有点高了，橙比较合适。

### 题意

按顺序执行一系列操作：

1. 增加一个特定物品
2. 减少一个特定物品
3. 增加一个任意物品

要求判断操作 2 能否全部执行，如果能则求出每次操作 3 增加的物品。

### 分析

贪心：对于操作 2 减少物品 $x$ 时，如果之前的操作 1 已增加了 $x$，则可行；否则如果之前还有空余的操作 3 没有用上，则可行；否则不行。

实现上，由于物品在 $[1,1000]$ 之间，可以开一个桶 $a$ 存目前有的物品，用一个计数器存放到目前为止操作 3 的数量，并用一个栈存放答案。

需要注意，对于没用完的操作 3，我们用任何物品补齐即可。（一开始还因为这个 WA 了一次）

### 代码

```c
#include <stdio.h>
int a[1005], stk[1005];
int cnt, top;
int main() {
    int n; scanf("%d", &n);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        if (x > 0) a[x]++;
        else if (x < 0) {
            x = -x;
            if (a[x]) a[x]--;
            else if (top < cnt) stk[++top] = x;
            else { puts("No"); return 0; }
        }
        else cnt++;
    }
    puts("Yes");
    for (int i = 1; i <= top; i++) printf("%d ", stk[i] ? stk[i] : 1);
    return 0;
}
```

---

## 作者：jsisonx (赞：0)

# 题目分析
输入 $n$ 个数字 $a_1,a_2,a_3...a_n$，如果如果 $a_i$ 为正，相当于往仓库在放入一个数字 $a_i$ ,如果 $a_i$ 为负，相当于从仓库中取出一个数字 $-a_i$ ,如果 $a_i$ 为 $0$，那么相当于往仓库中放入一个万能的数字，如果要取出一个仓库中没有的数，可以用 $0$ 代替。

显然，可以用一个 $visit$ 数组表示仓库中 $visit_i$ 这个数的个数，$out$ 数组表示 $0$ 代替的数，遇到负数 $i$ 时先看 $visit_{-i}$ 是否大于 $0$。如果大于 $0$ 就优先消耗仓库中 $-i$ 的个数，即 ```visit[i]--```，实在 $-i$ 没有了，再看有没有代替的 $0$。如果连 $0$ 都没有了，那一定无法完成，输出 ```No```，否则 $0$ 的个数减一，将这个 $0$ 代替的数（也就是 $-i$ 加入 $out$ 数组中）。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,visit[100001]={0},a[100010],timesOf0=0,h=0,outOf0[100001]={0},no=0,yes=1;
int main(){
	cin>>n;
	while(n--){
		int temp;
		cin>>temp;
		if(no==1){
			continue;
		}
		if(temp<0){
			if(visit[-temp]>=1){
				visit[-temp]--;
				continue;
			}
			if(timesOf0>0){
				timesOf0--;
				outOf0[h++]=-temp;
				continue;
			}
			cout<<"No";
			no=1;
			yes=0;
		}
		if(temp==0){
			timesOf0++;
		}
		if(temp>0){
			visit[temp]++;
		}
	}
	if(yes==0){
		return 0;
	}
	cout<<"Yes"<<endl;
	for(int i=0;i<h;i++){
		cout<<outOf0[i]<<" ";
	} 
	return 0;
}
```
这样就能 AC 吗？不行。这样会出现```wrong output format Unexpected end of file - int32 expected```的错误。因为题目其实要求是：输出用过的 $0$ 所代替的数字后，还要把没用过的 $0$ 表示的数也输出。显然输出任何数都可以。

# AC 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,visit[100001]={0},a[100010],timesOf0=0,h=0,outOf0[100001]={0},no=0,yes=1;
int main(){
	cin>>n;
	while(n--){
		int temp;
		cin>>temp;
		if(no==1){
			continue;
		}
		if(temp<0){
			if(visit[-temp]>=1){
				visit[-temp]--;
				continue;
			}
			if(timesOf0>0){
				timesOf0--;
				outOf0[h++]=-temp;
				continue;
			}
			cout<<"No";
			no=1;
			yes=0;
		}
		if(temp==0){
			timesOf0++;
		}
		if(temp>0){
			visit[temp]++;
		}
	}
	if(yes==0){
		return 0;
	}
	cout<<"Yes"<<endl;
	for(int i=0;i<h;i++){
		cout<<outOf0[i]<<" ";
	}
	for(int i=0;i<timesOf0;i++){
	    cout<<1<<' ';
	}
	return 0;
}
```





---

## 作者：Wy_x (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P6956)

刚学会用 $\text{map}$，发篇题解记录一下。

### 题意：
1. 当 $a_i$ 为正数时，**提供**一个为 $a_i$ 的魔法物品。
1. 当 $a_i$ 为负数时，**消耗**一个为 $-a_i$ 的魔法物品。
1. 当 $a_i$ 为 $0$ 时，**提供一个任意的**魔法物品。

### 解法：

- 开一个 $\text{map}$ 存储现在还剩多少值为 $a_i$ 的魔法物品。
- 如果 $a_i > 0$，直接记录进 $\text{map}$。
- 如果 $a_i < 0$，分情况讨论：
1. 如果现在有这个魔法物品，则 $\text{map}$ 中记录的数量 $-1$；
1. 如果现在没有有这个魔法物品，但有万能的魔法物品 $(a_i=0)$，则消耗一个万能的，同时把 $-a_i$ 记录进数组里，计数器 $+1$；
1. 如果都没有，输出 $\text{No}$，并结束程序。
- 如果能活到最后，输出 $\text{Yes}$，换行，再输出万能魔法物品换成了什么魔法物品。

### 代码：


------------


```cpp
#include<bits/stdc++.h>   //万能头文件  
#define reg register
#define int long long
using namespace std; 
map<int,int>mp;//开map
int a[10000001],tot,cnt,n,x;
//tot:存 a[0] 总数
//cnt:存万能魔法物品变为一般魔法物品的数量
//a:存万能魔法物品变为了什么魔法物品
//x：临时变量
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) 
	{
		cin>>x;
		if(x>0) mp[x]++;//大于 0，直接存入 map
		else if(x==0) tot++;//等于 0，a[0] 总数加一
		else
		{
			if(mp[-x]) mp[-x]--;//如果现在有这个魔法物品，计数器减一
			else
			{
				if(tot-cnt>0)//如果还有万能魔法物品，则改这个万能魔法物品为一般魔法物品，cnt+1
				{
					cnt++;
					a[cnt]=-x;
				}
				else//上面的条件都不满足，就挂了
				{
					cout<<"No"<<endl;
					return 0;
				}
			}
		}
	}
	cout<<"Yes\n";
	for(int i=1;i<=cnt;i++) cout<<a[i]<<" ";
	for(int i=cnt+1;i<=tot;i++) cout<<"1 ";//以防万能魔法物品没有用完，输出 1
	cout<<endl;
	return 0;
}
```

---

## 作者：wdgm4 (赞：0)

## 思路

使用桶和贪心算法。

由于 $a_i$ 的数据范围很小，我们可以用桶存储英雄拥有的所有种类的魔法物品的数量，在需要消耗魔法物品时判断桶里这种魔法物品的数量是否大于 $0$。

再考虑 $a_i$ 为 $0$ 的魔法生物，我们可以先把它留着，等到需要消耗魔法物品但是那种魔法物品没有时再使用，把它提供哪种魔法物品存在答案数组里，如果当前没有可以使用的 $a_i$ 为 $0$ 的魔法生物且需要消耗魔法物品但是那种魔法物品没有时再使用时直接输出 `No` 即可，否则最后输出答案，如果有还未使用的 $a_i$ 为 $0$ 的魔法生物，输出任意数即可。

## 代码

```cpp
#include<bits/stdc++.h> 
#define XD 114514
#define MAXN 1010
using namespace std;
int n,num,k,b[MAXN];
int a[MAXN];
int main(){
	cin>>n;
	for(int i=1,nem;i<=n;i++){
		cin>>nem;
		if(nem==0){//情况一 
			num++;
		}else if(nem>0){//情况二 
			a[nem]++;
		}else{//情况三 
			if(a[-nem]) a[-nem]--;//记得取反 
			else{
				if(num>0){//如果有尚未使用的 a_i 为 0 的魔法生物 
					num--;
					b[++k]=-nem;
				}else{
					cout<<"No";
					return 0;//直接结束程序 
				}
			}
		}
	}
	cout<<"Yes\n";
	for(int i=1;i<=k;i++) cout<<b[i]<<" ";
	for(int i=1;i<=num;i++) cout<<1<<" ";//输出任意数即可 
	return 0;
}

```


---

## 作者：xiaoqian02 (赞：0)

### 第一部分：翻译
既然现在还没有翻译，就大概写一下题意。

[大概题意](https://www.luogu.com.cn/paste/dn8r81lp)

### 第二部分：思路
首先，观察一下数据范围，发现有 $-1000 \le a_i \le 1000$。再结合题目，容易想到开一个桶来解决，用一个数组 `t[1005]` 储存每种类型物品的个数，在 `t[0]` 中存储独角兽的个数。

对于每个生物，

1. 若该生物是善良的，直接收下。

2. 若该生物是邪恶的，分三种情况讨论。

	- 若有对应砍掉它的物品，直接用。独角兽要留着救急。
    
   - 如果没有对应物品但有独角兽，就只能用独角兽来救急。因为不用就挂掉了。
   
   - 如果都没有，那没救了，读入完直接输出 `No`。
3. 最后，若该生物是独角兽，就 `t[0]++`，存在 `t[0]` 里。

### 第三部分：防入坑指南
- 在遇到邪恶生物时，注意存储时要用相反数或绝对值。

- 如果独角兽没用完，剩下的一定要输，全部输 $1$ 就可以（当然如果你想用 `rand` 请自便）。

### 第四部分：代码
~~估计最让人开心的就是这部分了……~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,t[1005],a[1005],cnt,nm;
//a数组保存独角兽变什么，t数组保存物品，nm存独角兽个数
bool p=1;//有没有中途结束
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);//两句cin优化
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        if(p==0) continue;//如果已经挂了，读完就结束掉
        if(x>0) t[x]++;
        else if(x<0)//这里注意全部要 -x
        {
            if(t[-x]) t[-x]--;
            else if(t[0])
            {
                t[0]--;
                a[++cnt]=-x;//保存独角兽用途
            }
            else p=0;
        }
        else t[0]++,nm++;
    }
    if(p==0) cout<<"No"<<endl;
    else
    {
        cout<<"Yes"<<endl;
        for(int i=1;i<=cnt;i++) cout<<a[i]<<" ";
        for(int i=1;i<=nm-cnt;i++) cout<<"1 ";//剩下的全部输出 1
        cout<<endl;
    }
    return 0;
}
```

---

