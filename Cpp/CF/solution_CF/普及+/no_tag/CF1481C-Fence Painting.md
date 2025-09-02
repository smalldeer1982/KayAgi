# Fence Painting

## 题目描述

You finally woke up after this crazy dream and decided to walk around to clear your head. Outside you saw your house's fence — so plain and boring, that you'd like to repaint it.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1481C/31e7d7ee4094f34ab2e6d6908f5b67e5f8eebe96.png)You have a fence consisting of $ n $ planks, where the $ i $ -th plank has the color $ a_i $ . You want to repaint the fence in such a way that the $ i $ -th plank has the color $ b_i $ .

You've invited $ m $ painters for this purpose. The $ j $ -th painter will arrive at the moment $ j $ and will recolor exactly one plank to color $ c_j $ . For each painter you can choose which plank to recolor, but you can't turn them down, i. e. each painter has to color exactly one plank.

Can you get the coloring $ b $ you want? If it's possible, print for each painter which plank he must paint.

## 样例 #1

### 输入

```
6
1 1
1
1
1
5 2
1 2 2 1 1
1 2 2 1 1
1 2
3 3
2 2 2
2 2 2
2 3 2
10 5
7 3 2 1 7 9 4 2 7 9
9 9 2 1 4 9 4 2 3 9
9 9 7 4 3
5 2
1 2 2 1 1
1 2 2 1 1
3 3
6 4
3 4 2 4 1 2
2 3 1 3 1 1
2 2 3 4```

### 输出

```
YES
1
YES
2 2
YES
1 1 1
YES
2 1 9 5 9
NO
NO```

# 题解

## 作者：RE_Prince (赞：2)

# CF1481C Fence Painting

[link](https://www.luogu.com.cn/problem/CF1481C)

## Sol

一道（大）模拟。

首先，这道题应该倒序思考，因为如果遇到一个粉刷匠刷的颜色和哪一个都对不上，可以让他刷以前的粉刷匠刷过的木板，因为终究是要被覆盖的。

因此，我们要考虑如下几种情况：

- 有可以刷的木板，刷完后颜色改变成想要的颜色。

- 有可以刷的木板，刷完后颜色不变。

- 没有可以刷的木板，但刷一些特定的木板会被以后的粉刷匠覆盖掉。

- 没有可以刷的木板，也不会被覆盖掉。

在这里，只有第四种可以判错，其他的都可以用 `vector` 记录位置后判断解决。其中有一个 `vector` 记录哪些位置需要被再次粉刷，另一个记录哪些位置不用被粉刷，可以让刷这个颜色的且没有木板可修改的粉刷匠来消耗一次。

注意一下细节，就过了（细节在代码中给）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,i,j,k;
int a[100009],b[100009],c[100009],ans[100009];
vector<int> G[100009],G2[100009];
int cnt[100009];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(i=1;i<=100000;i++) G[i].clear(),G2[i].clear();//多测清空
		memset(cnt,0,sizeof(cnt));
		map<int,int> mp,mp2;
		for(i=1;i<=n;i++) cin>>a[i];
		for(i=1;i<=n;i++) cin>>b[i];
		for(i=1;i<=m;i++) cin>>c[i];
		for(i=1;i<=n;i++) 
			if(a[i]!=b[i]) mp[b[i]]++,G[b[i]].push_back(i);//两个颜色不同，要刷
			else G2[b[i]].push_back(i),mp2[b[i]]=1;//相同，不用刷，为了让这个颜色的粉刷匠消耗一次机会
		int pos=0;//记录哪个地方可以随便刷,终究是要被覆盖的
		for(i=m;i>=1;i--)
		{
			if(mp[c[i]]) //检测到这个颜色有要改的
				mp[c[i]]--;
				ans[i]=pos=G[c[i]][cnt[c[i]]];
				cnt[c[i]]++;
			}
			else 
			{
				if(!pos&&!mp2[c[i]])//如果没有可以随便刷的木板且没有和他颜色相同的木板,直接退 
				{
					puts("NO");
					goto end;
				}
				else if(pos) ans[i]=pos;//乱刷
				else ans[i]=pos=G2[c[i]][0];//相同颜色的木板随便刷
			}
		}
		for(i=1;i<=m;i++)
			if(mp[c[i]]) 
			{
				puts("NO");
				goto end;
			}
			else a[ans[i]]=c[i];
		for(i=1;i<=n;i++)//验证一下
			if(a[i]!=b[i])
			{
				puts("NO");
				goto end;
			}
		puts("YES");
		for(i=1;i<=m;i++) cout<<ans[i]<<" ";
		puts("");
		end:;
	}
	return 0;
}
```

---

## 作者：chlchl (赞：2)

思维难度好像不太高，主要是代码实现 + 分讨。

正好刚回归，码力和逻辑思维能得到一个不错的回升。

## Solution
显然从末尾考虑，这样的话每一个木板的颜色就是第一次涂到它身上的颜色（显然在倒序下，后遍历到的是实际顺序前的，会被覆盖掉）。

这样能衍生出两个重要的涂色方法：
1. 要是遇到一个没用的颜色，就涂到一块已经被涂过的木板上（因为它最后一定会被覆盖）。
2. 每块木板涂的第一个颜色必须是目标颜色 $b_i$，因为涂了之后就没法修改了。

那么我们从后往前扫 $c_i$：
- 如果这个颜色下还有木板，涂到其中一块；
- 如果这个颜色下没了（这个颜色没用），随便涂到一块已经被涂色的木板上；
- 如果这个颜色没用、没有已经被涂色的木板，涂到其中一块同色木板上；
- 如果这个颜色没用、没有已经被涂色的木板、没有同色木板，无解。

最后要看看还有没有颜色不对的木板。

剩下的就是实现了，要维护什么基本上都清楚了。本题偏模拟，故贴个代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int T, n, m, ans[N], a[N], b[N], c[N], col[N];
vector<int> g[N];

void solve(){
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++)
		g[i].clear(), col[i] = -1;
	for(int i=1;i<=n;i++)
		scanf("%d", &a[i]);
	for(int i=1;i<=n;i++){
		scanf("%d", &b[i]);
		if(a[i] != b[i])
			g[b[i]].push_back(i);
		else if(a[i] == b[i])
			col[a[i]] = i;
	}
	for(int i=1;i<=m;i++)
		scanf("%d", &c[i]);
	int lst = -1;
	for(int i=m;i>=1;i--){
		if(g[c[i]].size() > 0)
			lst = ans[i] = g[c[i]].back(), g[c[i]].pop_back();
		else if(lst != -1)
			ans[i] = lst;
		else if(col[c[i]] != -1)
			ans[i] = lst = col[c[i]];
		else
			return printf("NO\n", i), void(0);
	}
	for(int i=1;i<=n;i++)
		if(g[i].size() > 0)
			return printf("NO\n"), void(0);
	printf("YES\n");
	for(int i=1;i<=m;i++)
		printf("%d ", ans[i]);
	printf("\n");
	return ;
}

int main(){
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
}
```


---

## 作者：xuezhe (赞：2)

考虑倒序操作。

如果还有地方 $a_i \neq b_i$，且 $b_i = c_j$，就令第 $j$ 个人刷第 $i$ 个板，否则任找一个 $b_i=c_j$ 的 $i$ 板刷，或找后面任意一个工人将会刷的板刷，如果都没地方刷则无解。

Code:

```cpp
int T,n,m,a[100005],b[100005],c[100005],d[100005],o[100005];
vector<int> f[100005];
int main(){
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;++i)
            cin>>a[i];
        for(int i=1;i<=n;++i)
            cin>>b[i];
        for(int i=1;i<=m;++i)
            cin>>c[i];
        for(int i=1;i<=n;++i)
            d[i]=0,f[i].clear();
        for(int i=1;i<=n;++i){
            d[b[i]]=i;
            if(a[i]!=b[i])
                f[b[i]].push_back(i);
        }
        bool flg=true;
        for(int i=m;i;--i){
            if(f[c[i]].size()){
                o[i]=f[c[i]].back();
                f[c[i]].pop_back();
            }else if(d[c[i]]){
                o[i]=d[c[i]];
            }else if(i!=m){
                o[i]=o[m];
            }else{
                flg=false;
                break;
            }
        }
        if(flg)
            for(int i=1;i<=n;++i)
                if(f[i].size())
                    flg=false;
        if(flg){
            puts("YES");
            for(int i=1;i<=m;++i)
                printf("%d ",o[i]);
            putchar(10);
        }else{
            puts("NO");
        }
    }
    return 0;
}
```



---

## 作者：龙潜月十五 (赞：2)

## 一、前言

一道 **模拟** 题，因为细节很多 WA 了好几发，故记录一下。个人感觉我思路还算清晰。

## 二、题意

有 $n$ 个木板，初始颜色为 $a_i$，你希望将其涂成 $b_i$。有 $m$ 个木匠依次出现，第 $i$ 个木匠 **一定** 要选一个木板涂成 $c_i$。问最后每个木板能否涂成你希望涂成的颜色。

## 三、思路

首先我们会发现后面涂的颜色会覆盖之前的颜色，因此就算之前的涂色可能会不满足条件，之后的涂色也有可能将其覆盖，使其满足条件。因此我们考虑 **倒序** 考虑每个木匠的涂色。

对于第 $i$ 个木匠的涂色 $c_i$，会有四种情况：

1. 有一个 $b_i$ 等于 $c_i$，且 $a_i$ 等于 $b_i$；

2. 有一个 $b_i$ 等于 $c_i$，且 $a_i$ 不等于 $b_i$；

3. 没有一个 $b_i$ 等于 $c_i$，且在第 $i$ 个木匠前有涂色；

4. 没有一个 $b_i$ 等于 $c_i$，且在第 $i$ 个木匠前没有涂色。

显然我们依次考虑四种情况，前三种都是满足条件的，第四种就是无解的情况。具体实现因为还要输出每个木匠涂的木板，因此用 `vector` 来存每个颜色的位置。

最后还要判一下涂色有没有 $b_i$ 不等于 $a_i$ 的情况，有的话则无解。

**多组数据一定要清空**！我就是这里 WA 了。

## 四、代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read() {
    ll sum = 0, ff = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') {
            ff = -1;
        }
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
    	sum = sum * 10 + ch - 48;
        ch = getchar();
    }
    return sum * ff;
}

const int N = 1e5 + 7;
int t, n, m, a[N], b[N], c[N], ans[N];
vector<int>same[N], dif[N], ed;
bool flag;

int main() {
	t = read();
	while(t--) {
		flag = true;
		ed.clear();
		for(int i = 1; i <= n; i++)
			same[i].clear(), dif[i].clear();
		
		n = read(), m = read();
		for(int i = 1; i <= n; i++)
			a[i] = read();
		for(int i = 1; i <= n; i++) {
			b[i] = read();
			if(a[i] == b[i])
				same[b[i]].push_back(i);
			else
				dif[b[i]].push_back(i);
	}
		for(int i = 1; i <= m; i++)
			c[i] = read();
		
		for(int i = m; i >= 1; i--)
			if(!dif[c[i]].empty())
				ans[i] = dif[c[i]][dif[c[i]].size() - 1], ed.push_back(ans[i]), same[c[i]].push_back(ans[i]), dif[c[i]].pop_back();
			else if(!same[c[i]].empty()){
				ans[i] = same[c[i]][0];
				ed.push_back(ans[i]);
			}
			else if(!ed.empty())
				ans[i] = ed[0];
			else {
				flag = false;
				printf("NO\n");
				break;
			}
			
		for(int i = 1; i <= n; i++)
			if(!dif[i].empty() && flag) {
				flag = false;
				printf("NO\n");
				break;		
			}
			
		if(flag) {
			printf("YES\n");
			for(int i = 1; i <= m; i++)
				printf("%d ", ans[i]);
			printf("\n");
		}
	}
    return 0;
}

```


---

## 作者：huayucaiji (赞：2)

本题细节较多，因此我在 45min 通过时，只有 600 人左右通过。

首先容易想到倒序考虑，因为后来者的颜色肯定在上面。我们可以记录一下 $a,b$ 中有多少颜色需要更换，有哪些颜色不需要更换。我们在考虑颜色时，首先考虑的就是那些需要更改的颜色，如果现在要考虑的颜色已经不再需要了，就选择下一个要涂的人所涂的那个栅栏即可，这样下一个人会盖过现在的颜色。

细节贼多，注意数组清空。

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=1e5+10;

int n,m,a[MAXN],b[MAXN],c[MAXN],ans[MAXN],tot;
stack<int> cnt[MAXN];
int ex[MAXN];

signed main() {
	int t=read();
	while(t--) {
		n=read();m=read();
		tot=0;
		for(int i=1;i<=n;i++) {//细节，清空数组
			int sz=cnt[i].size();
			while(sz--) {
				cnt[i].pop();
			}
			ex[i]=0;
		}
		for(int i=1;i<=n;i++) {
			a[i]=read();
		}
		for(int i=1;i<=n;i++) {
			b[i]=read();
			if(b[i]!=a[i]) {
				if(cnt[b[i]].empty()) {
					tot++;//有多少种颜色需要更改
				}
				cnt[b[i]].push(i);
			}
			ex[b[i]]=i;//记录那些颜色出现
		}
		for(int i=1;i<=m;i++) {
			c[i]=read();
		}
		
		int last=0;
		bool flag=1;
		for(int i=m;i;i--) {
			if(!cnt[c[i]].empty()) {
				ans[i]=cnt[c[i]].top();
				cnt[c[i]].pop();
				if(cnt[c[i]].empty()) {
					tot--;
				}
			}
			else {
				if(last==0) {
                    //即考虑最后一个粉刷匠，单独处理
					if(ex[c[i]]) {
						ans[i]=ex[c[i]];
					}
					else {
                        //没地方画，输出NO
						printf("NO\n");
						flag=0;
						break;
					}
				}
				else {
					ans[i]=last;
				}
			}
			last=ans[i];
		}
		if(flag&&tot) {
            //若颜色不够用，没有改好，输出NO
			printf("NO\n");
		}
		else if(flag){
			printf("yEs\n");
			for(int i=1;i<=m;i++) {
				printf("%lld ",ans[i]);
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Theophania (赞：0)

先比较初始状态和目标状态，两者不同说明需要粉刷，标记这些位置等人来刷。

工人必须按顺序粉刷，但是有时候并不需要他来刷，这时有两种选择：

1. 如果他的颜色出现在篱笆上，他可以刷到那个颜色相同的位置，也就相当于没刷；
2. 如果篱笆上不该出现他的颜色，他必须刷在一个会被后面的工人覆盖的位置。

所以按照时间逆序模拟，只要有人涂上了正确的颜色，就可以让前面所有涂错的人都涂在这里。

实现的时候稍微注意一下细节即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
template <typename T>
inline void read(T &x)
{
    T data = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        data = (data << 3) + (data << 1) + ch - '0';
        ch = getchar();
    }
    x = f * data;
}
template <typename T, typename... Args>
inline void read(T &t, Args &...args)
{
    read(t);
    read(args...);
}
const int maxn = 1e5 + 9;

vi p[maxn];
int a[maxn], b[maxn], c[maxn], color[maxn], ans[maxn];
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        int n, m, done = 0;
        bool flag = true;
        read(n, m);
        for (int i = 1; i <= n; ++i)
            read(a[i]);
        for (int i = 1; i <= n; ++i)
        {
            read(b[i]);
            if (a[i] != b[i])
                p[b[i]].push_back(i); // 标记需要粉刷的位置
            else
                color[b[i]] = i; // 标记第一种选择的位置
        }
        for (int i = 1; i <= m; ++i)
            read(c[i]);
        for (int i = m; i; --i)
        {
            if (!p[c[i]].empty())
            {
                ans[i] = p[c[i]].back();
                p[c[i]].pop_back();
                if (!done)
                    done = ans[i]; // 可以让前面的人刷在这里
            }
            else if (done) // 第二种选择
                ans[i] = done;
            else if (color[c[i]]) // 第一种选择
            {
                ans[i] = color[c[i]];
                done = ans[i];
            }
            else
            {
                flag = false;
                break;
            }
        }
        for (int i = 1; i <= n; ++i)
            if (!p[i].empty())
            {
                flag = false;
                break;
            }
        if (flag)
        {
            cout << "YES\n";
            for (int i = 1; i <= m; ++i)
                cout << ans[i] << ' ';
            cout << '\n';
        }
        else
            cout << "NO\n";
        for (int i = 1; i <= n; ++i)
        {
            p[i].clear();
            color[i] = 0;
        }
    }
    return 0;
}
```


---

