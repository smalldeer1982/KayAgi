# Too Many Impostors (easy version)

## 题目描述

This is an interactive problem. The only difference between the easy and hard version is the limit on number of questions.

There are $ n $ players labelled from $ 1 $ to $ n $ . It is guaranteed that $ n $ is a multiple of $ 3 $ .

Among them, there are $ k $ impostors and $ n-k $ crewmates. The number of impostors, $ k $ , is not given to you. It is guaranteed that $ \frac{n}{3} < k < \frac{2n}{3} $ .

In each question, you can choose three distinct integers $ a $ , $ b $ , $ c $ ( $ 1 \le a, b, c \le n $ ) and ask: "Among the players labelled $ a $ , $ b $ and $ c $ , are there more impostors or more crewmates?" You will be given the integer $ 0 $ if there are more impostors than crewmates, and $ 1 $ otherwise.

Find the number of impostors $ k $ and the indices of players that are impostors after asking at most $ 2n $ questions.

The jury is adaptive, which means the indices of impostors may not be fixed beforehand and can depend on your questions. It is guaranteed that there is at least one set of impostors which fulfills the constraints and the answers to your questions at any time.

## 说明/提示

Explanation for example interaction (note that this example only exists to demonstrate the interaction procedure and does not provide any hint for the solution):

For the first test case:

Question "? 1 2 3" returns $ 0 $ , so there are more impostors than crewmates among players $ 1 $ , $ 2 $ and $ 3 $ .

Question "? 3 4 5" returns $ 1 $ , so there are more crewmates than impostors among players $ 3 $ , $ 4 $ and $ 5 $ .

Outputting "! 3 4 1 2" means that one has found all the impostors, by some miracle. There are $ k = 3 $ impostors. The players who are impostors are players $ 4 $ , $ 1 $ and $ 2 $ .

For the second test case:

Question "? 7 1 9" returns $ 1 $ , so there are more crewmates than impostors among players $ 7 $ , $ 1 $ and $ 9 $ .

Outputting "! 4 2 3 6 8" means that one has found all the impostors, by some miracle. There are $ k = 4 $ impostors. The players who are impostors are players $ 2 $ , $ 3 $ , $ 6 $ and $ 8 $ .

## 样例 #1

### 输入

```
2
6

0

1

9

1```

### 输出

```
? 1 2 3

? 3 4 5

! 3 4 1 2

? 7 1 9

! 4 2 3 6 8```

# 题解

## 作者：Tyyyyyy (赞：5)

# CF1617D1

#### 题意简述
- 有 $n$ 个人（$n$ 是 $3$ 的倍数），其中有 $k$ 个是骗子（$\frac{n}{3}<k<\frac{2n}{3}$），其余人是普通人。
- 你可以进行若干次询问，如 `? a b c` 所示（要求 $a,b,c$ 互不相同且都在 $1\sim n$）。
- 作为对询问的回答，你会得到一个整数 $0$ 或 $1$。若为 $0$，表示编号为 $a,b,c$ 的三个人中，骗子多于普通人；若为 $1$，表示普通人多于骗子。
- 进行最多 $2n$ 次询问，找到骗子的数量和所有骗子的编号。
- $6 \leq n < 10^4$，数据组数满足 $1 \leq t \leq 100$。

#### 题目分析
如果能找到两个人，且知道他们一个是骗子，一个是普通人，则我们可以利用他们得知剩余所有人的身份（只需要将想要得知身份的人与这两个人一起提问即可）。

要找到这两个人，我们可以采用对每三个相邻的人提问的办法。这样的三个人一共有 $n-2$ 组。因为 $\frac{n}{3}<k<\frac{2n}{3}$，所以其中必然有相邻的两组答案不同。设这两组分别为 $\{i,i+1,i+2\},\{i+1,i+2,i+3\}$，则 $i+1$ 与 $i+2$ 身份必然不同。我们再用 $i+1,i+2$ 对其他所有人提问即可。

总共用了 $(2n-4)$ 次询问。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[10010];
int ans[10010],cnt;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n-2;i++)
		{
			printf("? %d %d %d\n",i,i+1,i+2);
			fflush(stdout);
			scanf("%d",&a[i]);
		}
		int x,y,xx,yy;
		for(int i=1;i<n-2;i++)
			if(a[i]!=a[i+1]){x=i+1,y=i+2;break;}
		int rec;cnt=0;
		for(int i=1;i<=n;i++)
		{
			if(i==x||i==y)continue;
			printf("? %d %d %d\n",x,y,i);
			fflush(stdout);
			scanf("%d",&rec);
			if(rec==0)ans[++cnt]=i,xx=i;
			else yy=i;
		}
		printf("? %d %d %d\n",xx,yy,x);
		fflush(stdout);
		scanf("%d",&rec);
		if(rec==0)ans[++cnt]=x;
		printf("? %d %d %d\n",xx,yy,y);
		fflush(stdout);
		scanf("%d",&rec);
		if(rec==0)ans[++cnt]=y;
		printf("! %d ",cnt);
		for(int i=1;i<=cnt;i++)printf("%d ",ans[i]);
		puts("");
		fflush(stdout);
	}
	return 0;
}
```

---

## 作者：123zbk (赞：1)

因为坏人的个数 $\dfrac{n}{3}<k<\dfrac{2n}{3}$，所以我们只要对每三个相邻的人提问，一共有 $n-2$ 组，必定有两组答案不同。

设这两组为 $\{i,i+1,i+2\}$ 和 $\{i+1,i+2,i+3\}$，那么 $i+1$ 和 $i+2$ 一定一好一坏。我们用这两个人和其他的任意一个人进行询问，这个答案就代表着这个人的好坏。最后再用另外的两个人去检验 $i+1$ 和 $i+2$ 的好坏即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e4+5;
int T,n,a[maxn],x,y,xx,yy,cnt,op,ans[maxn];
int main()
{
	cin>>T;
	while(T--)
	{
		cnt=0;
		cin>>n;
		for(int i=1;i<=n-2;i++)
		{
			cout<<"? "<<i<<" "<<i+1<<" "<<i+2<<endl;
			cin>>a[i];	
		}
		for(int i=1;i<n-2;i++)
		{
			if(a[i]!=a[i+1])
			{
				x=i+1;
				y=i+2;
				break;
			}	
		}	
		for(int i=1;i<=n;i++)
		{
			if(i==x||i==y)
			{
				continue;
			}
			cout<<"? "<<x<<" "<<y<<" "<<i<<endl;
			cin>>op;
			if(op==0)
			{
				ans[++cnt]=i;
				xx=i;
			}
			else
			{
				yy=i;
			}
		}
		cout<<"? "<<xx<<" "<<yy<<" "<<x<<endl;
		cin>>op;
		if(op==0)
		{
			ans[++cnt]=x;
		}
		else
		{
			ans[++cnt]=y;
		}
		cout<<"! "<<cnt<<" ";
		for(int i=1;i<=cnt;i++)
		{
			cout<<ans[i]<<" ";
		}
		cout<<endl;
	}	
	return 0;
} 
```

---

## 作者：Priestess_SLG (赞：0)

考虑对于四个人 $a$，$b$，$c$，$d$。两次询问分别询问 $a,b,c$ 和 $b,c,d$。若两次询问的结果不一样，则说明 $b$ 和 $c$ 一定不同类别。找出这样的一组 $b$ 和 $c$ 之后将其和所有其他人做询问，就可以得到其他人的类别。最后任选一个已经确定的好人和一个已经确定的坏人，就可以询问出 $b$ 的类别，那么 $c$ 的类别也就确定了。具体见代码。

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define int long long
using namespace std;
const int N = 1000100, mod = 998244353;
int a[N], res[N];
signed main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n - 2; ++i) {
            cout << "? " << i << ' ' << i + 1 << ' ' << i + 2 << endl;
            int o ; cin >> o ; 
            res[i] = o;
        }
        int id = -1;
        for (int i = 1; i < n - 2; ++i) {
            if (res[i] != res[i + 1]) {
                id = i;
                break;
            }
        }
        // id + 1, id + 2
        vector<int> good, bad;
        for (int i = 1; i <= n; ++i) {
            if (i != id + 1 && i != id + 2) {
                cout << "? " << i << ' ' << id + 1 << ' ' << id + 2 << endl;
                int o ; cin >> o ; 
                if (o == 1) {
                    good.eb(i);
                } else {
                    bad.eb(i);
                }
            }
        }
        cout << "? " << good[0] << ' ' << bad[0] << ' ' << id + 1 << endl;
        int o ; cin >> o;
        if (o == 1) {
            good.eb(id + 1);
            bad.eb(id + 2); 
        } else {
            good.eb(id + 2);
            bad.eb(id + 1); 
        }
        cout << "! " << bad.size() << ' ' ;
        for (auto &x : bad) {
            cout << x << ' ';
        }
        cout << endl;
    }
    return 0;
}

/*



*/

```

---

## 作者：happybob (赞：0)

如果我们能找到一个好人和一个坏人，我们就可以在 $n-2$ 次询问内确定每个人的身份。

如何找呢？我们对每三个相邻的人进行一次询问。由于 $k$ 的限制，所以必然存在两组三个相邻的人结果不同。而这两组中的其中两个人的身份不变，所以我们就可以找出那两个人。总共询问 $n-2$ 次。

所以总共询问次数 $2n-4$ 次，符合条件。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int N = 1e4 + 5;

int t, n;

int id1, id2;
vector<int> v;

int query(int a, int b, int c)
{
	printf("? %d %d %d\n", a, b, c);
	fflush(stdout);
	int x;
	scanf("%d", &x);
	return x;
}

void solve()
{
	int last = -1;
	for (int i = 1; i + 2 <= n; i++)
	{
		int p = query(i, i + 1, i + 2);
		if (last != -1 && last != p)
		{
			id1 = i - 1, id2 = i + 2;
			if (p == 0) v.emplace_back(id2);
			else v.emplace_back(id1);
			break;
		}
		last = p;
	}
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		v.clear();
		v.shrink_to_fit();
		id1 = id2 = 0;
		solve();
		for (int i = 1; i <= n; i++)
		{
			if (i != id1 && i != id2)
			{
				int p = query(id1, id2, i);
				if (p == 0) v.emplace_back(i);
			}
		}
		printf("! %d ", v.size());
		for (auto& i : v) printf("%d ", i);
		fflush(stdout);
	}
	return 0;
}
```


---

## 作者：Ignotus (赞：0)

题意：交互题，给定一个长度为 $n$ 的 $01$ 序列，其中 $0$ 的个数 $k$ 满足 $\frac{n}{3}<k<\frac{2n}{3}$。每次询问一组 $a,b,c$，交互库会返回 $a,b,c$ 位置上三个数中出现的 $0$ 次数更多还是 $1$ 次数更多。要求通过不超过 $2n$ 次询问得到原序列中哪些位置是 $0$。  

发现如果我们已经确定了原序列中一个 $0$ 的位置和一个 $1$ 的位置，则可以用 $n-2$ 次询问得到剩余位置的情况（因为每次询问可以让 $a,b$ 分别等于两个已经确定的位置，这时返回的值一定与 $c$ 位置上的数相同）。  

考虑依次询问 $(1,2,3),(2,3,4),\dots,(n-2,n-1,n)$ 来确定一个 $0$ 的位置和一个 $1$ 的位置。当相邻的两组询问 $(i,i+1,i+2),(i+1,i+2,i+3)$ 返回结果不同时，则 $i$ 位置上和 $i+3$ 位置上的数一定不相等，根据返回的结果即可确定 $i$ 位置上和 $i+3$ 位置上的数具体是 $0$ 还是 $1$。  

总共询问 $2n-4$ 次。  

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;
using ll = long long;

#define pb push_back

int T, n;
int lst, cur, pos;

vector <int> imp;

void work(){
	imp.clear();
	cin >> n;
	cout << "? 1 2 3" << endl;
	cin >> lst;
	for(int i = 2; i <= n - 2; ++i){
		cout << "? " << i << " " << i + 1 << " " << i + 2 << endl;
		cin >> cur;
		if(lst != cur){
			pos = i + 2;
			if(lst == 0) imp.pb(pos - 3);
			else imp.pb(pos);
			break;
		}
		else lst = cur;
	}
	for(int i = 1; i <= n; ++i){
		if(i == pos - 3 || i == pos) continue;
		cout << "? " << i << " " << pos - 3 << " " << pos << endl;
		cin >> cur;
		if(!cur) imp.pb(i);
	}
	cout << "! " << imp.size() << " ";
	for(int i = 0; i < (int)imp.size(); ++i) cout << imp[i] << " ";
	cout << endl;
}

int main(){
	cin >> T;
	while(T--) work();
	return 0;
}
```


---

