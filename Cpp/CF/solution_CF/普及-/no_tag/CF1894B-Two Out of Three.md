# Two Out of Three

## 题目描述

给定一个数组 $a_1, a_2, ..., a_n$。你需要找到一个数组 $b_1$, $b_2$, ..., $b_n$，其中包含数字 $1, 2, 3$，使得以下三个条件中恰好有两个条件被满足：

- 存在 $1\le i, j\le n$，使得 $a_i=a_j,b_i=1,b_j=2$。
- 存在 $1\le i, j\le n$，使得 $a_i=a_j,b_i=1,b_j=3$。
- 存在 $1\le i, j\le n$，使得 $a_i=a_j,b_i=2,b_j=3$。

如果不存在这样的数组 $b$，请报告不可以。

## 样例 #1

### 输入

```
9
6
1 2 3 2 2 3
7
7 7 7 7 7 7 7
4
1 1 2 2
7
1 2 3 4 5 6 7
5
2 3 3 3 2
3
1 2 1
9
1 1 1 7 7 7 9 9 9
1
1
18
93 84 50 21 88 52 16 50 63 1 30 85 29 67 63 58 37 69```

### 输出

```
1 2 3 1 1 1 
-1
3 2 2 1 
-1
2 1 2 1 3 
-1
1 1 2 2 1 2 2 3 3
-1
3 2 1 3 3 3 3 2 2 1 1 2 3 1 3 1 1 2```

# 题解

## 作者：MagicLyney_06 (赞：6)

### 前言

昨天在寝室熬夜打的这场比赛，好困...

### 题目大意

给出一个数组 $a_1,a_2,\dots,a_n$，求出一个可以恰好满足（记住是恰好，昨晚上卡了我好久！）其中两条性质的数组 $b_1,b_2,\dots,b_n$，或不可以则输出 `-1`。

### 题目分析

由于数据范围很小，$a_i$ 最大也才 $100$，所以可以直接开一个数组 $num$ 来存每个数出现的次数。首先来看哪些情况是无解的。其实很显然， 如果出现次数大于等于 $2$ 的数个数小于 $2$，那自然就无解。剩下的即为有解情况。

对于构造，我们可以直接人为的令它只满足性质一和性质二（当然，你也可以选择别的组合）。数组范围很小，可以直接暴力遍历一遍。如果这个数出现次数为 $1$ 次，那对答案没有影响，你可以随便给他们赋一个你喜欢的数。如果出现多次，那就对答案有影响了。我们直接让第一对多次的数满足性质一，其余全部满足性质二（主要是我懒，你也可以选别的）。每有一个数 $a_i$，就 `num[a[i]]--`。如果 `num[a[i]]` 变到了 $0$，则给它赋 $2$ 或 $3$，否则全部赋成 $1$。这样就可以简单暴力的构造出数组 $b$ 了。

还要注意，$num$ 数组记得一定要清空！

### AC代码

```cpp
//
// Created by lndff on 2023.11.07
//
#include <bits/stdc++.h>
 
using namespace std;
int num[110], a[110];
bool check[110];//判断每个数对答案有无影响
int main(){
    // freopen("B.in","r",stdin);
    // freopen("B.out","w",stdout);
    int t;
    cin >> t;
    while (t--){
        memset(num, 0, sizeof(num));
        memset(check, 0, sizeof(check));//清空数组
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; scanf("%d", &a[i]), num[a[i]]++, i++);
        int jk = 0;
        for (int i = 1; i <= 100; i++){
            if (num[i] >= 2) jk++, check[i] = 1;//统计有贡献数字个数，同时标记它们
        }
        if (jk <= 1) {puts("-1");continue;}//不合法情况，输出“-1”
        int add = 0;//记录该赋2还是3
        for (int i = 1; i <= n; i++){//每个数以此找到对应的b[i]
            num[a[i]]--;
            if (!num[a[i]] && check[a[i]]){//对答案有贡献且是这个数最后一次出现
                if (!add){
                    printf("2 ");
                    add = 1;//接下来的全部赋成3
                }
                else printf("3 ");
            }
            else printf("1 ");//不是最后一个或对答案没贡献
        }
        puts("");//提行
    }    
}
```



---

## 作者：fuxuantong123 (赞：1)

# CF1894B Two Out of Three 题解
## 思路
因为题目需要**恰好**满足 $2$ 个条件，所以至少需要 $2$ 个都在数组中重复出现了至少 $2$ 次的数。

>如果只有一个重复出现的数，要让它满足条件就必须出现三次，构造为 $1$、$2$ 和 $3$，这样就会全部满足三个条件，所以不行。

至于其他的没有重复的数，随便赋一个值就行了。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[110];
int ans[110];
vector<int> t[110];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		for(int i=0;i<=100;i++){
			t[i].clear();
			ans[i]=0;
		}
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			t[a[i]].push_back(i);
		}
		int cnt=0;
		for(int i=0;i<=100;i++){
			if(t[i].size()>=2){
				cnt++;
			}
		}
		if(cnt<=1){
			printf("-1\n");
			continue;
		}
		int z=0;
		for(int i=0;i<=100;i++){
			if(t[i].size()>=2){
				for(int j=0;j<(t[i].size()-1);j++){
					ans[t[i][j]]=1;
				}
				ans[t[i][(t[i].size()-1)]]=(z==0?2:3);
				z^=1;
			}
		}
		for(int i=1;i<=n;i++){
			if(ans[i]==0){
				ans[i]=1;
			}
			printf("%d ",ans[i]);
		}
		printf("\n");
	}
return 0;
}
```


---

## 作者：梦应归于何处 (赞：1)

### 思路

这题实际上很简单，题目中给了我们三个条件但实际上我们就考虑前 $2$ 种情况就行了。

观察到这题数组中的值最大才 $100$ 所以我们可以考虑把每个数对应的位置都存下来，然后做处理。

我们去循环 $1,2,3\dots 100$ 然后去看有几个位置是这个数。

如果只有一个，那么就直接让这个 $b$ 数组对应的位置为 $1$。

如果有两个及以上，那么我们让前两个所对应的 $b$ 数组中的位置分别为 $1,2$ 或 $1,3$。

最后我们要看，如果同时有 $2$ 和 $3$ 那么就输出 $b$ 数组，否则就输出 $-1$。

### 代码

~~~cpp
#include <bits/stdc++.h>
#define db double
#define ll long long
#define ex exit(0)
#define endl "\n"
#define inl inline
#define null NULL
#define pb(a) push_back(a)
using namespace std;
ll a[105], b[105];
ll cnt[105];
vector<ll> v[105];
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll t;
	cin >> t;
	while (t--) {
		ll n;
		cin >> n;
		for (int i = 1; i <= 100; i++) {
			cnt[i] = 0;
			v[i].clear();
		}
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			cnt[a[i]]++;
			v[a[i]].push_back(i);
		}
		ll tw = 0;
		for (int i = 1; i <= 100; i++) {
			if (cnt[i] == 0) {
				continue;
			}
			if (cnt[i] == 1) {
				b[v[i][0]] = 1;
				continue;
			}
			b[v[i][0]] = 1;
			b[v[i][1]] = (tw == 0 ? 2 : 3);//为了方便我们就只让第一个长度大于等于二所对应的位置为2，其余位置都为3。
			tw = 1;
			for (int j = 2; j < v[i].size(); j++) {
				b[v[i][j]] = 1;
			}
		}
		bool have2 = 0, have3 = 0;
		for (int i = 1; i <= n; i++) {
			if (b[i] == 2) {
				have2 = 1;
			} else if (b[i] == 3) {
				have3 = 1;
			}
		}
		if (have2 && have3) {
			for (int i = 1; i <= n; i++) {
				cout << b[i] << " ";
			}
			cout << endl;
		} else {
			cout << "-1\n";
		}
	}
	return 0;
}
~~~

---

## 作者：ganpig (赞：1)

三个条件中 $1,2,3$ 的地位是平等的，因此可以钦定 $b_i=1,b_j=3$ 和 $b_i=2,b_j=3$ 这两个满足，而 $b_i=1,b_j=2$ 不满足。

一组 $a_i$ 相同的下标的 $b_i$ 显然是不能同时包含 $1,2,3$ 三个数的，不然三个条件就都满足了。

于是我们要找出两组 $a_i$ 相同的下标（至少两个才算“组”，找不出两组则无解），一组的 $b_i$ 为 $1$ 和 $3$，另一组的 $b_i$ 为 $2$ 和 $3$，其余组只要保证每组的 $b_i$ 相同即可。

一种简单的构造方法：全部初始化为 $3$，两组的第一个分别设为 $1$ 和 $2$。具体实现见代码。

### $\text{Code}$

```cpp
#include <bits/stdc++.h>

void solve() {
    int n, x, cnt = 0;
    std::cin >> n;
    std::vector<int> pos[101], ans(n, 3);
    for (int i = 0; i < n; i++)
        std::cin >> x, pos[x].emplace_back(i);
    for (int i = 1; i <= 100; i++)
        if (pos[i].size() >= 2 && (ans[pos[i].front()] = ++cnt) == 2) {
            for (int x : ans)
                printf("%d ", x);
            return putchar('\n'), void();
        }
    puts("-1");
}

int main() {
    int T;
    std::cin >> T;
    while (T--)
        solve();
    return 0;
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

简简单单构造题，就是要认真读题，是能且只能满足两个条件。

我们可以考虑每种数字，如果数字只有一个，是不能满足任何一个条件的，那就随便给一个 $b$ 即可。

如果这个数字有多个，那么就只能有两种 $b$，否则就会满足三个条件，所以一种数字最多满足一种条件。

所以，如果只有一个或者甚至没有两个及以上的数字，那么必定无解。

再来考虑如何构造，可以直接钦定一种数字满足一个条件，其他所有数字满足另一种条件。

因为只是构造题，只要合理就可以随便造，所以可以先选一个出现多次的数字为特殊数字，然后把所有数字的非最后一个都给 $1$，然后对于每种数字的最后一种，如果是特殊数字，就给 $2$，否则就给 $3$。

这样，必定有一种数字（特殊数字）满足条件 $1$，其他出现多次的数字满足条件 $2$，其他数字不满足任何条件，这样就恰好满足两个条件。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[105],num[105],res,f;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n),f=res=0;
		for(int i=1;i<=100;++i) num[i]=0;
		for(int i=1;i<=n;++i) scanf("%d",&a[i]),++num[a[i]],res+=(num[a[i]]==2);
		if(res<2){printf("-1\n");continue;}
		for(int i=1;i<=n;++i)
		{
			if(num[a[i]]==1)
			{
				if(f==a[i]) printf("2 ");
				else printf("3 ");
			}
			else f=(!f&&num[a[i]]>1)?a[i]:f,printf("1 "),--num[a[i]];
		}
		puts("");
	}
	return 0;
}

```

---

## 作者：wanghaoran00 (赞：0)

### 思路
因为恰好有两个条件被满足，每个条件是等效的，显然 $b_{i}$ 不能同时包含 $1,2,3$，所以根据题意需找到 $a_{1}=a_{2}$，$a_{3}=a_{4}$，$a_{1}\ne a_{3}$ 同时满足，使用桶排，若序列中出现两次以上两数相等即符合条件，分别将出现相同的数的第一次输出 $2$ 和 $3$ 其余输出 $1$，否则输出 $-1$。（多测不清空，爆零两行泪）

ACcode
```
#include<bits/stdc++.h>
using namespace std;
void read(int &p){
	int k=1;
	p=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-'){
			k=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		p=p*10+c-'0';
		c=getchar();
	}
	p*=k;
	return ;
}
int T,n,a[105],t[105],b,cnt1,cnt2;
signed main(){
	read(T);
	while(T--){
		memset(a, 0, sizeof(a));
     		memset(t, 0, sizeof(t));
		b=0,cnt1=0,cnt2=0;
		read(n);
		for(int i=1;i<=n;i++){
			read(a[i]);
			t[a[i]]++;
		}
		for(int i=1;i<=100;i++){
			if(b==2){
				break;
			}
			if(t[i]>=2){
				if(b==1){
					cnt2=i;
				}
				if(b==0){
					cnt1=i;
				}
				b++;
			}
		}
		if(b!=2){
			puts("-1");
		}
		else{
			for(int i=1;i<=n;i++){
				if(a[i]==cnt1){
					cout<<"2 ";
					cnt1=-1;
				}
				else if(a[i]==cnt2){
					cout<<"3 ";
					cnt2=-1;
				}
				else{
					cout<<"1 ";
				}
			}
			puts("");
		}
	}
	return 0;
}

```

---

## 作者：ZZZZZZZF (赞：0)

# 题意

给定一个序列 $a_1,a_2,\dots,a_n$，找出一个由且必须由 $1,2,3$ 组成的新序列 $b_1,b_2,\dots,b_n$，使其满足且只满足以下性质中的两条：

1. 存在 $1 \le i , j \le n$，使 $a_i = a_j,b_i = 1,b_j = 2$
2. 存在 $1 \le i , j \le n$，使 $a_i = a_j,b_i = 1,b_j = 3$
3. 存在 $1 \le i , j \le n$，使 $a_i = a_j,b_i = 2,b_j = 3$

如果不存在这样的序列 $b$ 输出 $-1$。

# 思路

手玩数据找结论：
1. 对于序列 $a$ 中三个相等的数，其对应的序列 $b$ 中的数不能同时为 $1,2,3$，否则将同时满足三条性质。那么对于序列 $a$ 中一组相同的数，其对应 $b$ 序列中的数要么只由 $1,2$ 组成，要么只由 $1,3$ 组成，要么只由 $2,3$ 组成，要么全部相同。

2. 必须同时出现这三种组合中的两种。

所以只需找出两组相同的数，然后给对应的序列 $b$ 中的数赋值为 $1,2,2 \dots$ 和 $1,3,3 \dots$ 。

对于 $b$ 中其他位置，全部赋值为 $1$ 即可保证不满足任何性质。

# Code

```cpp
//A题把心态搞爆炸了，代码写的很乱QwQ

#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        //sgc:相同数的组数
        int n,a[1000],b[1000],sgc = 0,vis[1000];
        memset(b,0,1000);
        memset(vis,0,1000);
        cin>>n;
        for(int i = 1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int j = 1;j<=n;j++){
        
            if(vis[j])continue;
            
            //snc:相同数的数量
            int num = a[j],snc = 0;
            vis[j] = 1;
            for(int k = 1;k<=n;k++){
                if(k == j)continue;
                if(a[k] == num){
                    if(snc == 0){
                        sgc++;
                        b[j] = 1;
                        snc++;
                    }
                    snc++,vis[k] = 1;
                    
                    //把b[k]赋值为2或3
                    b[k] = sgc+1;
                }
            }
            if(sgc == 2){
                for(int k = 1;k<=n;k++)
                    if(b[k] == 0) b[k] = 1;
                break;
            }
        }

        if(sgc<2)
            printf("-1");
        else
            for(int j = 1;j<=n;j++)
                printf("%d ",b[j]);
            
        printf("\n");
    }
    return 0;
}

```

---

## 作者：technopolis_2085 (赞：0)

首先，题目要求只满足两个条件，则对于 $i$ 而言：

对于每一个 $a_j$ 使得 ${a_j}=i$，则：

- 所有 $b_j$ 都为 $1$ 和 $2$。
- 所有 $b_j$ 都为 $1$ 和 $3$。
- 所有 $b_j$ 都为 $2$ 和 $3$。

否则，必然满足全部三个条件。

然后判断无解。

如果数组中出现次数大于等于 $2$ 的数小于两个，则无解。因为这种情况无法满足两个条件。

判断完无解之后，根据要求，可以将出现次数大于等于 $2$ 的数交替填 $1$、$2$  和 $1$、$3$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=110;
int a[maxn];
int cnt[maxn];
int ans[maxn];

int main(){
	int T;
	scanf("%d",&T);
	
	while (T--){
		memset(cnt,0,sizeof(cnt));
		int n;
		scanf("%d",&n);
		
		int tot=0;
		for (int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			cnt[a[i]]++;
		}
		
		for (int i=1;i<=100;i++){
			if (cnt[i]>=2) tot++;
		}
		
		if (tot<2){
			printf("-1\n"); continue;
		}
		
		int flag=0;
		for (int i=1;i<=100;i++){
			if (cnt[i]==0) continue;
			if (cnt[i]>=2) flag^=1;
			
			if (flag==1){
				int op=1;
				for (int j=1;j<=n;j++){
					if (a[j]==i){
						ans[j]=op; op=3-op;
					}
				}
			}else{
				int op=1;
				for (int j=1;j<=n;j++){
					if (a[j]==i){
						ans[j]=op; op=4-op;
					}
				}
			}
		}
		
		for (int i=1;i<=n;i++) printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}
```


---

