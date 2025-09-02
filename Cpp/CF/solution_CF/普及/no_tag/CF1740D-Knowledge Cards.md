# Knowledge Cards

## 题目描述

### 题目大意
对于一个 $n \times m$ 的棋盘，左上角为 $(1,\;1)$，右下角为 $(n,\;m)$。$(1,\;1)$ 和 $(n,\;m)$ 上分别有一个栈。最开始的时候$(1,\;1)$ 格子上的栈里有 $k$ 张牌，**从栈顶到栈底**的第 $i$ 张牌上有一个数 $a_i$，保证 $a$ 数组是一个 $k$ 的全排列。你需要对这些牌做若干次操作将所有牌移到 $(n,\;m)$ 格子的栈中，使得最后 $(n,\;m)$ 格子的栈中从上到下牌上的序号依次为 $1 \sim k$，每次给你棋盘长宽 $n \times m$ 和初始的 $a$ 数组，请问是否有解。

我们定义一次操作的规则如下：

1. 一次只能操作一张牌；
2. 一张牌只能向相邻的**四联通**格子（有共边）里移动；
3. **除了** $(1,\;1)$ 和 $(n,\;m)$ 以外的格子内不能拥有超过一张牌；
4. 如果你当前**操作**的格子是 $(1,\;1)$，那么你只能从他的**栈顶**取走一张牌，且你**不能**将一张牌移到他上面；
5. 如果你当前操作的**目标**格子是 $(n,\;m)$，那么你只能将一张牌移动到他的**栈顶**，且你不能从他上面移走任何一张牌。

## 样例 #1

### 输入

```
4
3 3 6
3 6 4 1 2 5
3 3 10
1 2 3 4 5 6 7 8 9 10
5 4 4
2 1 3 4
3 4 10
10 4 9 3 5 6 8 2 7 1```

### 输出

```
YA
TIDAK
YA
YA```

# 题解

## 作者：yingkeqian9217 (赞：1)

`set` 练习题。

不难想到可以使用一个指针 $id$ 从 $1$ 到 $n$ 进行遍历，遍历过程中将经过的元素用 `set` 储存。而对于当前需要填入终点~~站~~栈的元素 $op$，我们如果遍历到了，只要保证当前 `set` 内元素 $\le n \times m -4$ 就可以跳过，否则无解；如果是已经在 `set` 中的，直接 `erase` 即可。

如何证明呢？我们先来看一个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/gdvti15t.png)

没错，数字华容道大家都玩过，显然只要有一格是空的，最终就一定能拼成有序的样子。这道题也一样，除去 $( 1 , 1 )$ $( n , m )$ 以及 $op$，还要剩下一个空位，才能保证 $op$ 能入槽，于是 $n \times m -4$ 就这样得来了。同理已经在 `set` 中的，因为前一步的 `set` 大小 $\ge$ 当前的，所以显然必定合法。

## Code:

```
#include<bits/stdc++.h>
#define maxn 2900001
using namespace std;
int T,n,m,k,op,id,a[maxn];
void solve(){
	set<int>s;
	scanf("%d%d%d",&n,&m,&k);
	op=k,id=1;
	for(int i=1;i<=k;i++) scanf("%d",&a[i]);
	while(op>0){
		if(s.find(op)!=s.end()){//已经进入set的
			s.erase(op);
			op--;
			continue;
			}
		while(a[id]!=op&&id<=k) s.insert(a[id]),id++;//指针后挪
		if(s.size()>n*m-4) op=0;
		id++,op--;//跳过当前元素
	}
	if(op==-1) printf("TIDAK\n");
	else printf("YA\n");
}
signed main(){
	scanf("%d",&T);
	while(T--){solve()}
	return 0;
}

```

---

## 作者：linyihdfj (赞：1)

## CF1740D Knowledge Cards
想要更优质的阅读体验，就来[这里](https://www.cnblogs.com/linyihdfj/p/16893607.html)吧。
### 题目分析：
我们肯定是让最大的先到，然后次大的然后慢慢来。

所以对于其他牌来说，只要我们最大的一个还没有出现，就必须在某一个位置等着，但是一旦最大值出现就必须有办法让它走。

我们发现这里的 “有办法让它走” 其实就是等价于至少有一个位置是空的，所以我们就考虑一个个出牌，记录牌桌上最多同时会存在多少张牌。

如果牌数大于 $n \times m - 2$ 显然就是不合法的，减二是因为 $(1,1)$ 和 $(n,m)$ 不算啊。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e6+5;
int n,m,k,sum[N];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&m,&k);
		int mx = 0,now = k;
		set<int> st;
		for(int i=1; i<=k; i++){
			int a;scanf("%d",&a);
			st.insert(a);
			while(!st.empty() && st.find(now) != st.end()){
				st.erase(now);now--;
			}
			mx = max(mx,int(st.size()));
		}
		if(mx >= n * m - 3)	printf("TIDAK\n");
		else	printf("YA\n");
	}
	return 0;
}
```


---

## 作者：Halberd_Cease (赞：1)

~~临了给整出来了~~

![](https://cdn.luogu.com.cn/upload/image_hosting/aezfiiiu.png)

主要就是一个思想，然后实现也比较简单。

 **定理：** 如果这个棋盘上有至少一个空位，那么总有一种方法可以让棋盘上任何一个卡片移到任何一个位置。
 
 **证明：** 
 
 - **公理1：** 空位置可以转到其上下左右任何一个位置。
 
 - **定理1：** 空位置可以转到棋盘上任意一个位置。
 
 - **证明：** 重复公理1即可。
 
 - **定理2：** 任意一个卡片可以转到其上下左右任意一个位置。
 
 - **证明：** 根据定理1，将空位置转移到目标位置即可。
 
 - **定理3：** 任意一个卡片可以转到棋盘上任意一个位置。
 
 - **证明：** 重复定理2即可。
 
 于是题目就很简单了，哪一个卡片在哪里不重要，我们关注的是那些卡片在场上（不在 $(1,1)$ 和 $(n,m)$ ），我们从 $n$ 到 $1$ 枚举需要的卡片，如果场上没有就去 $(1,1)$ 从上往下开，如果开的卡片把棋盘占满了就无解，如果到最后都没有占满就无解。
 
 **Code**:
 
 ```cpp
void work()
{
    se.clear();
    int x,y;
    cin>>x>>y;
    int n;
    cin>>n;
    int now=n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)
    {
        if(a[i]!=now)
        {
            se.insert(a[i]);
            if(se.size()>=x*y-3)
            {
                cout<<"TIDAK\n";
                return ;
            }
        }
        else
        {
            now--;
            while(se.find(now)!=se.end())
            {
                se.erase(now);
                now--;
            }
        }
    }
    cout<<"YA\n";
}
```



---

## 作者：UniGravity (赞：0)

## Solution CF1740D Knowledge Cards

[传送门](https://www.luogu.com.cn/problem/CF1740D) 

### 题目分析
首先介绍一个思想：在棋盘上**至少存在一个空位**的情况下，棋盘上的**任意卡片**都能移到**任意位置**。   
实际上理解起来也不难，借鉴[数字华容道](https://baike.baidu.com/item/%E6%95%B0%E5%AD%97%E5%8D%8E%E5%AE%B9%E9%81%93)的思想，空格可以被转移到任意地方，然后便可移动目标卡片。

那么显然卡片的具体摆放位置就无需考虑，只需考虑当前剩下的空格数量。

由于终点无法进行跳栈操作，显然我们需要让到达终点的卡片**有序**，那么我们就有以下几种操作方式：
* 对于最大的卡片，我们一步到位把它移到终点即可。（按照数字华容道的方式移动）

* 对于不是最大的卡片，我们把它移动到棋盘的其他位置（除起点、终点外）（可以理解为给最大的卡片移出位置）。

判断条件也可以得出：
* 如果在任意时刻棋盘的空余位置仅剩一个，即无法进行移动操作，此时判定为 `TIDAK`。

* 否则如果全部牌都处理完毕，则输出 `YA`。

那么如何找到当前（除终点外）的最大卡片呢？   
我们可以使用 `set` 记录和删除卡片，每个测试样例时间复杂度 $O(k\log k)$。

### 完整代码
具体讲解在代码中写了。

```cpp
#include <bits/stdc++.h>
using namespace std;

int T;
int n, m, k;
int a[1000005];

int cnt;
set< int > st; // 记录的是棋盘上最大的卡片
int maxa;
bool flag;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &m, &k);
        
        st.clear();
        maxa = k; // 当前最大
        flag = false;
        
        for (int i = 1; i <= k; i++) {
            scanf("%d", &a[i]);
            
            if (a[i] == maxa) {
                maxa--; // 一步到位
                // 把已经可以移到终点的卡片移到终点
                while (!st.empty() && st.find(maxa) != st.end()) {
                    st.erase(maxa);
                    maxa--;
                }
            } else {
                st.insert(a[i]); // 移到棋盘（临时区）
                // 空余位置大小小于1
                if (st.size() >= n * m - 3) {
                    flag |= true;
                }
            }
        }
            
        if (flag) printf("TIDAK\n");
        else printf("YA\n");
    }
    return 0;
}
```

完结撒花~~~

---

## 作者：Daidly (赞：0)

一个结论：

- 在一个 $n\times m$ 的网格图上有些格子放有不同的卡片，若至少有一个格子上没有放置，则一定能在有限移动卡片次数内将其中一个卡片移到指定位置。

---

证明可以考虑空格子四周卡片的移动情况。对于此题，除去 $(1,1),(n,m)$ 和刚拿出的卡片需要放置的位置 $(1,2)$ 或 $(2,1)$，若在移动过程中每次至少有一个为空即可完成操作。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int K=1e5+5;
int n,m,k,a[K],pos[K];

int main(){
	int T=read();
	while(T--){
		n=read(),m=read(),k=read();
		for(int i=1;i<=k;++i){
			a[i]=read();
			pos[a[i]]=i;
		}
		int l=0,num=0;
		bool flag=1;
		for(int i=k;i>=1;--i){
			if(pos[i]<=l)num--;
			else{
				num+=pos[i]-l;
				if(num<=n*m-3)num--;
				else{
					flag=0;
					break;
				}
				l=pos[i];
			}
		}
		if(flag)puts("YA");
		else puts("TIDAK");
	}
	return 0;
}
```

---

