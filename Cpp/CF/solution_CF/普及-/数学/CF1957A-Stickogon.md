# Stickogon

## 题目描述

给定 $n$ 个木棍，第 $i$ 个长度为 $a_i$。

你需要保证：

* 构成的任意多边形每一边由一根木棍构成。

* 没有木棍用于多个多边形的边。

求通过这些木棍同时能构造的**正**多边形数量。

注：不可以破坏木棍。

## 说明/提示

对于第一组数据，显然一根木棍无法构造多边形。

对于第二组数据，显然两根木棍也无法构造多边形。

对于第三组数据，可以用四根长度为 $3$ 的木棍构造一个正方形。

对于第四组数据，可以用五根长度为 $2$ 的木棍构造一个五边形，然后用四根长度为 $4$ 的木棍构造一个正方形。


对于全部数据，满足 $1\le t,n,a_i\le100$。

## 样例 #1

### 输入

```
4
1
1
2
1 1
6
2 2 3 3 3 3
9
4 2 2 2 2 4 2 4 4```

### 输出

```
0
0
1
2```

# 题解

## 作者：lihongqian__int128 (赞：7)

# CF1957A Stickogon题解
因为要求构成的**正**多边形数量最多，所以产生贪心思路：尽量构成三角形。

记长度为 $l$ 的木棍的数量为 $cnt_l$，则长度为 $l$ 的木棍最多形成 $\lfloor cnt_l \div 3\rfloor$ 个**正**多边形。

将长度为 $1\sim100$ 的木棍分别求解，求和即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std ;
int t , n , a , ans , cnt[105] ;
int main()
{
    cin >> t ;
    while(t--)
    {
        memset(cnt , 0 , sizeof cnt) ;
        ans = 0 ;
        cin >> n ;
        while(n--)
        {
            cin >> a ;
            cnt[a]++ ;
        }
        for(int i = 1 ; i <= 100 ; i++) ans += cnt[i] / 3 ;
        cout << ans << '\n' ;
    }
    return 0 ;
}
```

---

## 作者：MinimumSpanningTree (赞：5)

[原题链接](https://www.luogu.com.cn/problem/CF1957A)

题目求的是最多可以构造多少个正多边形，显然全部拼成边数最少的正三角形是最优的。

所以我们可以开一个桶，记录每个长度有多少根，除以 $3$ 后累加即可。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=110;
int t,n,a,c[N],cnt;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		cnt=0;
		for(int i=1;i<=100;i++) c[i]=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a);
			c[a]++;
		}
		for(int i=1;i<=100;i++) cnt+=c[i]/3;
		printf("%d\n",cnt);
	}
	return 0;
}
```

---

## 作者：gengchenghao (赞：4)

# 分析
此题很水，只要将所有边存桶，然后注意只有**三边及以上**才是多边形。  
要使多边形拼的尽量多就需要拼**三角形**，然后输出答案就好了。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
int main() {
	cin>>T;
	while(T--) {
		int n,a[10001]= {},ans=0,b[1001]={};
		cin>>n;
		for(int i=1; i<=n; i++) {
			cin>>a[i];
			b[a[i]]++;//入桶
		}
		for(int i=1; i<=101; i++) {
			ans+=b[i]/3;//能拼几个三角
		}
		cout<<ans<<endl;
	}
	return 0;
}

---

## 作者：_Chjich_ (赞：2)

# 题目大意
给出一堆木棒，求出最多可构造的 **正** 多变形的数量。
# 解题思路
关键看个 **正** 字。

这样我们就可以把长度相等的木棒放在一起，然后除以 $3$ （因为要有至少三条边才能构成一个封闭图形）
# 代码
```
#include <bits/stdc++.h>
using namespace std;
int T, a[105], n, x, ans, man;

void qk() {
	ans = 0, man = -999;
	for (int i = 1; i <= 100; i++)
		a[i] = 0;
}

int main() {
	cin >> T;
	while (T--) {
		qk();//清空
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> x, a[x]++, man = max(x, man);//用桶实现上面的做法。
		for (int i = 1; i <= man; i++)
			ans += a[i] / 3;
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：_sweetydd_ (赞：2)

# CF1957A  题解


------------
 **[题链](https://www.luogu.com.cn/problem/CF1957A)**

### 题目大意：

给定 $n$ 根小棒，每根长度为 $a_i$ ,求最多能摆出多少个**正多边形**。

------------

#### 思路：
用**桶排序**的思想，求出每种长度的小棒各有几根，由于最小的正多边形是三角形，所以直接**除以三**就可以求出 $n$ 根小棒**同时**能摆出的**最多**的正多边形啦

## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, a[110], t[110], ans;

int main() {
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= 100; i++) {
			t[i] = 0;//每次都要记得清空到100
		}
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			t[a[i]]++;//桶排
		}

		if (n < 3) {//小于三根直接输出0
			cout << 0 << endl;
			continue;
		} else {
			for (int i = 1; i <= 100; i++) {
				ans += t[i] / 3;
			}
		}
		cout << ans << endl;
		ans = 0;//记得清空
	}
	return 0;
}
```

---

## 作者：zhuxiangrui_2010 (赞：2)

# CF1957A Stickogon 题解
## 题意
给你 $t$ 组数据，每组数据有 $n$ 个小棒的长度，输出每组数据中所有的小棒最多能构成的正多边形的数量。
## 思路
这是[原题链接](https://www.luogu.com.cn/problem/CF1957A)。

这是[正多边形](https://answer.baidu.com/answer/land?params=Zu925Hzgy8HmylMKY1tSnk44zvd4qZKg87G3ECHPNnxdRzFEqeyAmemy%2BBklU0jNYjcKxhUrW8wWZIhO2m0qy2hCfdP%2FRgPu6h8y5NcflYK2rJRXtSaQ0FkvfH7nKPaYbuYQ9tiflHHBVOKB378UmZBC0ScTUXVgHL89Ec9HrEW%2BQHii7Q8PCGwqD%2B%2FXxAvyF2DGFRnjhqEzK59VQVLe0g%3D%3D&from=dqa&lid=f58c5c46002564cc&word=%E6%AD%A3%E5%A4%9A%E8%BE%B9%E5%BD%A2)。

~~根据资料~~我们可以了解道：
1. **正多边形各边一定相等。**
2. **边数最少的正多边形是正三角形。**

那么在能构成正多边形的数量中，小棒全部构成正三角形时，构成数量一定最多。

所以，我们只需要求出小棒最多能构成的正三角形的数量就可以了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		int n,a[110]={},s=0;
		cin>>n;
		for(int j=1;j<=n;j++){
			int x;
			cin>>x;
			a[x]++;
		}
		for(int i=1;i<=100;i++){
			s+=int(a[i]/3);
		}
		cout<<s<<endl;
	}
	return 1;//0
}
```

---

## 作者：InfiniteRobin (赞：1)

### 思路

------------
题目中要求只能拼**正多边形**，以及**没有木棍用于多个多边形的边**。那就先将木棍的长度进行排序，统计每种长度的木棍各有多少个。  
  
接下来，题目中求能构造的正多边形的最大数量，那肯定是把所有木棍都用来拼成三角形就可以啦！

------------
### AC CODE

------------
```cpp
#include<bits/stdc++.h>
using namespace std;

int t,n,a[1003];

int main(){
    cin>>t;
    //多测
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        //一定要排序
        sort(a+1,a+1+n);
        int cnt=0,ans=0;
        for(int i=1;i<=n;i++){
            if(a[i]!=a[i-1]){
                if(cnt>=3){
                    //全都拼成三角形
                    ans+=cnt/3;
                }
                //别忘重置
                cnt=1;
            }
            else{
                cnt++;
            }
        }
        //最后再处理一次
        if(cnt>=3){
            ans+=cnt/3;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```


------------
### THE END

---

## 作者：All_Unluck_Beginning (赞：1)

# CF1957A Stickogon

## 题意

题意十分简单，给予你 $n$ 个棍子，问这些棍子可以构成多少个正多边形。

## 思路

说是可以构成多少个正多边形，所以我们可以用边最少的正多边形等边三角形来计数。

在输入 $a$ 的时候，用一个数组 $f$ 来计算 $a$ 出现的次数，当 $f_{a}$ 等于 $3$ 时，答案加 $1$，$f_{a}$ 记为 $0$。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int t,n,a,f[105];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int ans=0;
		memset(f,0,sizeof(f));//别忘了初始化 
		for(int i=1;i<=n;i++){
			cin>>a;
			f[a]++;
			if(f[a]==3)ans++,f[a]=0;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：hexuchen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1957A)

[更好的阅读体验？](https://www.luogu.com.cn/article/qnyydfgy)

## 题目意思

告诉你 $n$ 根木棍的长度，求这些木棍最多能摆出几个多边形？

## 思路分析

首先，我们要知道，$1$ 根木棍或 $2$ 根木棍造不出多边形，只有 $3$ 根以上的木棍数才能造出多边形。

既然题目说的是最多，则说明我们要用尽量少的木棍来造每一个多边形。而耗材最少的多边形是三角形，所以我们要尽可能多的去造三角形。唯一的难点就是要记得用一个桶去装不同长度木棍的数量。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,tong[1001]; //桶
int main(){
	cin>>t;
    for(int i=1;i<=t;i++){
        cin>>n;
        memset(tong,0,sizeof(tong)); //要记得清空桶
        for(int j=1;j<=n;j++){
            int a;
            cin>>a;
            tong[a]++; //桶对应的小棒数量加一
        }
        int ans=0;
        for(int k=1;k<=1000;k++){ //遍历一遍桶
            if(tong[k]){ //如果桶里有小棒，这一步要记得，因为除数不能为零
                ans+=tong[k]/3; //摆尽量多的三角形
            }
        }
        cout<<ans<<'\n'; //输出
    }
	return 0; //完结撒花~
}
```

---

## 作者：TimelessWelkin (赞：0)

## 第一步：审题

题目要求：

1.构成的任意多边形每一边由一根木棍构成。

也就是指任意多边形每一遍木棍长度相同，不能用两根木棍及更多来拼成一条边。

2.没有木棍用于多个多边形的边。

也就是指一根木棍就参与一个多边形的构建，不会出现下图这种情况（图为草图，见谅）：

![图片](https://cdn.luogu.com.cn/upload/image_hosting/pqv4qhef.png)

## 第二步：设计算法

非常简单，一眼即可看出一个贪心。如果一个长度的木棍数量可以拼成正多边形（ $3$ 个及以上）则优先选择 $3$ 个。

可以用一个 $100$ 的数组来存储每一种长度的数量（记得清空数组）。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            int x;
            scanf("%d",&x);
            a[x]++;
        }
        int ans=0;
        for(int i=1;i<=100;i++){
            ans+=a[i]/3;
            a[i]=0; //多测，记得清零。这里比较懒，直接写在这里了。
        }
        printf("%d\n",ans);
    }
    return 0;//完结撒花。
}
```

---

## 作者：volatile (赞：0)

# 思路

首先看样例

```
4
1
1
2
1 1
6
2 2 3 3 3 3
9
4 2 2 2 2 4 2 4 4
```

首先可以肯定当 $t$ 为 $1$ 和 $2$ 时不能组成多边形，易知要组成最多的多边形，三角形更有性价比，观察样例 $t$ 为 $6$ 可以发现，只要用相同的木棍除以 $3$ 取整便是答案，可能会有人问了，那我用 $2$,$3$,$3$ 不就有 $2$ 种了吗？刚开始我也这么想，但题目说了，是**正多边形**，所以只需考虑相同木棍，用桶即可。

# 代码

```cpp
#include<iostream>
#include<string.h>
using namespace std;
int a[114];
int main()
{
    int n;
    cin>>n;
    while(n--){
        int t,sum=0;
        cin>>t;
        memset(a,0,sizeof(a));//注意清零
        while(t--){
            int x;
            cin>>x;
            a[x]++;
        }
        for(int i=1;i<=100;i++) sum+=a[i]/3;
        cout<<sum<<endl;
    }
    return 0;
}
```

---

## 作者：jsisonx (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1957A)
# 题目分析
题目需要求用给出的木棍长度拼出最多的正多边形。显然，每个正多边形所用的的木棍应该最少，因此，应该尽量多拼正三角形。所以可以先对木棍长度进行排序，保证相同长度的木棍一定排在一起。然后从第一根木棍开始枚举，如果发现连续三根相同长度的木棍，那么答案加一，然后再从第三根木棍后面的那一根开始重复执行上述步骤。如果发现剩余该长度木棍已经无法拼成正三角形了，那么直接跳到下一种长度，重复上述步骤。

# 代码

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,a[105]={0},ans=0;
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		sort(a,a+n);
		for(int i=0;i<n;){
			if(a[i]==a[i+1]&&a[i+1]==a[i+2]){
				ans++;
				i+=3;
				continue;
			}
			int f=a[i];
			while(a[i]==f){
				i++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Francium_ (赞：0)

# 思路
长度小于 $105$，可以用桶来记录每种长度的木棍的数量，然后我们知道，正三角形是边数最少的正多边形，所以每个 $a_i$ 去除以 $3$ 后累加就行了。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105];

int main() {
	int t;
	cin >> t;
	while (t--) {
		memset(a, 0, sizeof(a));
		int n, x, ans = 0;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> x;
			a[x]++;
		}
		for (int i = 1; i <= 100; i++)
			ans += a[i] / 3;
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Mashu77 (赞：0)

题意十分简单，给予你 $n$ 个棍子，问这些棍子可以构成多少个正多边形。

思路：
说是可以构成多少个正多边形，所以我们可以用边最少的正多边形等边三角形来计数。

在输入 $a$
 的时候，用一个数组 $f$
 来计算 $a$
 出现的次数，当 $f_a$
 等于 $3$
 时，答案加 $1$，$f_a$
 记为 $0$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,f[105];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int ans=0;
		memset(f,0,sizeof(f));//别忘了初始化 
		for(int i=1;i<=n;i++){
			cin>>a;
			f[a]++;
			if(f[a]==3)ans++,f[a]=0;
		}
		cout<<ans<<"\n";
	}
	return 0;
}

---

## 作者：dlzlj_2010 (赞：0)

注意到 $1\le a_i\le100$，值域极小，提示我们使用桶计数。  
处理完相同长度木棍数量后，考虑如何使构成的正多边形数量最多。显然，构造三角形是最划算的。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=105;
int a[N],b[N];

int main(){
	int T;
	cin>>T;
	while(T--){
		int n;cin>>n;
		memset(a,0,sizeof a);//原数组
		memset(b,0,sizeof b);//桶
		for(int i=1;i<=n;i++){
			cin>>a[i];
			++b[a[i]];//计数
		}
		int ans=0;
		for(int i=1;i<=N;i++){
			ans+=b[i]/3;//加上能构成的三角形数量
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1957A)

## 思路

考虑贪心。

因为用最少的木棍能组成的图形是正三角形，所以我们直接输出每个长度的木棍能组成的正三角形数量之和即可。由于 $1\le t,n,a_i\le 100$，所以我们直接枚举。设 $num_i$ 表示长度为 $i$ 的木棍的数量，答案简单来说就是：

$$\sum_{i=1}^{100} \lfloor \frac{num_i}{3}\rfloor$$

- 有多组测试数据，记得**清空变量**。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){//快读。
	ll k=0;bool flag=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')flag^=1;c=getchar();}
	while(c>='0'&&c<='9'){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	if(flag)return k;return -k;
}
const int N=110;
int tom[N];
signed main(){
	int T=read();
	while(T--){
		int n=read(),ans=0;
		for(int i=1;i<=n;++i)++tom[read()];
		for(int i=1;i<=100;++i){
			ans+=tom[i]/3;
			tom[i]=0;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/157562857)

---

## 作者：Melo_DDD (赞：0)

水题，但是还是挂了 $2$ 发，一定要好好思考再写题。

# 题目大意

略，多测一定要清空。

# 题目实现

看到数据范围，按题意模拟即可。

对于每个出现的长度，用栈存入然后离线询问，注意要开个 bool 数组避免重复入栈。

然后记录每个长度出现的次数，根据栈内信息遍历即可。

注意构成多边形的数量，其实是个小小的贪心：只要能构成多边形，我们尽量让它是正三角形，这样可以保证多边形数量是最多的，计算时向下取整即可。

没有什么用的特判：木棍数小于 $3$ 一定构不成多边形。

没什么用的卡常小技巧：快读。


## 代码：
```cpp
#include <bits/stdc++.h>
#define rep(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
const int N = 1e2 + 7 ;
int t ,stk[N] ,stop ,num[N] ,ans ,a ; 
bool instk[N] ;
namespace shin {
	template <typename T> inline void read (T &x) {
		x = 0 ;
		char ch = getchar () ;
		while (ch < '0' or ch > '9') {
			ch = getchar () ;
		}
		while (ch <= '9' and ch >= '0') {
			x = (x << 1) + (x << 3) + (ch ^ 48) ;
			ch = getchar () ;
		}
	}
	inline void init () {
		stop = 0 ;
		ans = 0 ;
		memset (stk ,0 ,sizeof (stk)) ; 
		memset (num ,0 ,sizeof (num)) ;
		memset (instk ,false ,sizeof (instk)) ;
	}
}
int main () {
	shin :: read (t) ;
	do {
		int n ;
		shin :: read (n) ;  
		shin :: init () ;
		rep (i ,1 ,n ,1) {
			shin :: read (a) ;
			if (instk[a]) goto her_ ;
			stk[++ stop] = a ;
			instk[a] = true ;
			her_ : ;
			num[a] ++ ; 
		}
		if (n < 3) {
			cout << 0 << '\n' ;
			goto her ;
		}
		rep (i ,1 ,stop ,1) {
			if (num[stk[i]] >= 3) ans += num[stk[i]] / 3 ;
		}
		cout << ans << '\n' ;
		her : ;
	} while (t -- != 1) ;
	return 0 ;
}
//kafka & かみや
```
###### 你是否承认卡芙卡和狼谷的美貌举世无双？

---

## 作者：_dbq_ (赞：0)

## 前言
没读题的同学可以点击[这里](https://www.luogu.com.cn/problem/CF1957A)先读题。

## 思路
由于它并没有要求大小，所以我们考虑用木棒用得最少得情况。在这种情况下，每三个相同长度的木棒可以拼成一个三角形，我们设长度为 $x$ 的木棒有 $cnt_x$ 根，得到如下公式：

$$\sum_{i=1}^{100}\lfloor\frac{cnt_x}{3}\rfloor $$

## 代码
```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<string>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#define LL long long
#define ULL unsigned long long
#define cint const int 
using namespace std;
cint INTINF=0x7f7f7f7f;
const LL LLINF=9e18;
int a[110];
inline auto read(){//快读
    auto x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main()
{
    #ifdef dbq
    freopen("CF1957A.in","r",stdin);
    freopen("CF1957A.out","w",stdout);
    #endif
    int T=read();
    while(T--)
    {
        memset(a,0,sizeof(a));//别忘初始化
        int ans=0,mx=-1,mn=110;
        cint n=read();
        for(int i=1;i<=n;i++)
        {
            cint x=read();
            a[x]++;//计数
            mx=max(mx,x);//算边界
            mn=min(mn,x);
        }
        if(n<=2)//特判两根木棒不能拼成多边形
        {
            cout<<0<<endl;
            continue;
        }
        for(int i=mn;i<=mx;i++)//优化区间范围
            ans+=int(a[i]*1.0/3);
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1957A)

### 思路

题目让我们构造多个多边形，使多边形的个数最多，因此我们只需要**让每一个多边形的边数尽量小**即可。而多边形的边数最小值为 $3$。因此我们只需要计算这 $n$ 个木棍能构成多少个三角形就可以了。

### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 110;

int t[N];

int main(){
	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++){
			int x;
			cin >> x;
			t[x]++;//计算 x 出现的次数。
		}
		int ans = 0;
		for(int i = 1; i <= 100; i++){
			ans += (t[i] / 3);//计算当边的长度为 x 时，最多能构成多少三角形。
			t[i] = 0;
		}
		cout << ans << endl;
	}
}
```

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1957A)
### 题意简述
现有 $n$ 根长度为 $a_1,a_2,...,a_n$ 的小棒，问能摆多少个**正**多边形
### 思路
本题其实很简单，首先我们用 $k$ 这个数组，记录长度为 $i$ 的木棒的个数，想要摆出**正多边形**，我们就必须要让这个多边形的每条边长度相等，而为了尽可能多的摆出多边形，我们可以将这些小棒全部用来摆三角形。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int k[10000];
int main()
{
    int t,n,s;
    cin>>t;
    for (int i=0;i<t;i++)
    {
        cin>>n;
        for (int j=0;j<n;j++)
        {
            cin>>s;
            k[s]=k[s]+1;
        }
        int ans=0;
        for (int j=1;j<=100;j++)
        {
            if (k[j]>2)
            {
                ans=ans+k[j]/3;
            }
            k[j]=0;
        }
        cout<<ans<<endl;
    }
}
```

---

## 作者：___nyLittleT___ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1957A)  
## 题意
给定 $n$ 根木棍，选择长度一样的 $x$ 根拼成 $x$ 边形，问最多拼多少个正多边形。  
## 定义
正多边形：所有边长相等的多边形，如三角形、正方形。  
**边数最少的多边形是三角形！**  
$1$ 条或者 $2$ 条边是拼不成图形的，更别说正多边形了。  
## 思路
要使正多边形数最多，那我们计算可以做多少个三角形就行了，因为它边数要求最少。这里我用了一点离散化的思想，把相同长度的边重新编号，设 $num$ 为有多少种不同长度的边。我们要计算的就是：  
$$\sum_{i=1}^{num}\frac{cnt_{i}}{3}$$
这是很好计算的。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,num,ans;
int b[105];//记录每种边有几条
int c[105];//重新编号
int main() {
	scanf("%d",&t);
	while(t--) {
		num=0,ans=0;//清空
		fill(b+1,b+101,0);//fill 函数对数组清空
		fill(c+1,c+101,0);
		scanf("%d",&n);
		for(int i=1; i<=n; i++) {
			scanf("%d",&a);
			if(c[a]==0) c[a]=++num;//重新编号，如果已经被编过了，就不用
			b[c[a]]++;//记录数量
		}
		for(int i=1; i<=num; i++) ans+=(b[i]/3);//制作正三角形
		printf("%d\n",ans);
	}
	return 0;
}
```

---

