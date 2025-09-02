# Football Kit

## 题目描述

Consider a football tournament where $ n $ teams participate. Each team has two football kits: for home games, and for away games. The kit for home games of the $ i $ -th team has color $ x_{i} $ and the kit for away games of this team has color $ y_{i} $ $ (x_{i}≠y_{i}) $ .

In the tournament, each team plays exactly one home game and exactly one away game with each other team ( $ n(n-1) $ games in total). The team, that plays the home game, traditionally plays in its home kit. The team that plays an away game plays in its away kit. However, if two teams has the kits of the same color, they cannot be distinguished. In this case the away team plays in its home kit.

Calculate how many games in the described tournament each team plays in its home kit and how many games it plays in its away kit.

## 样例 #1

### 输入

```
2
1 2
2 1
```

### 输出

```
2 0
2 0
```

## 样例 #2

### 输入

```
3
1 2
2 1
1 3
```

### 输出

```
3 1
4 0
2 2
```

# 题解

## 作者：封禁用户 (赞：2)

## CF432B Football Kit 题解
### 解题思路
观察可知，在主场时，无论如何都会使用主场球衣，所以我们只要统计这一只球队的客场球衣与多少主场球衣重合就行了。

注意不能使用 $O(n^{2})$ 的枚举，不然 $10^5$ 的数据会让你体验到 **TLE** 的滋味。

我们可以用一个 $10^5$ 的桶，将主场球衣记录下来，有效降低时间复杂度。

### 参考代码
```
#include<bits/stdc++.h>
using namespace std;
int n , x[100005] , y[100005] , z[100005];
int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for(int i = 0 ; i < n ; i++)
	{
		cin >> x[i] >> y[i];
		z[x[i]]++;
	}
	for(int i = 0 ; i < n ; i++)
	{
		cout << n + z[y[i]] - 1 << ' ' << n - z[y[i]] - 1 << endl;
	}
	return 0;
}
```

---

## 作者：Molina (赞：2)

# 题目大意：
[题目链接](https://www.luogu.com.cn/problem/CF432B)

共有 $ n $ 支球队，每一支球队会与另外的每支球队进行两场比赛（一次主场，一次客场），共有 $ n \times (n-1) $ 场比赛（翻译有误）。

每支球队都分别有主队服和客队服，编号分别为 $ x_i $ 与 $ y_i $。

当客队队服编号和主队队服相同时，就产生冲突，客队换成自己主队的队服。

求每支队伍主队服穿了几次，客队服穿了几次。
# 本题思路：
### 分析：
本题数据范围为 $ n \le 10^5 $，所以，用两重循环直接模拟是不行的，会超时一个点。

再重新看这道题，可以发现：每支球队都至少会穿 $ n-1 $ 次主队服，然后，只有当自己的客队服与其他球队的主队服产生冲突时，会再次穿主队服，不冲突时，就是穿客队服。

有了思路，就可以开始敲代码了。

### 步骤：
这里用了一个结构体。$ a $ 来输入每支球队的主客队服编号。输入时，用一个数组记录主队服的编号的个数。

然后开一重循环，分别进行记录（详细解释请见代码）。每支球队的穿主队服次数就是 $ n - 1 $ 次再加上数组中记录的，与自己的客队服冲突的球队的个数。每支球队的穿客队服次数就是 $ n - 1 $ 次减去冲突的次数，用 $ b $ 数组来记录。

然后便可以开心输出了！
# 代码来咯~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,ton[N];
struct cz{//结构体，不用也没事
	int x,y;
}a[N],b[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;//输入
		ton[a[i].x]++;//用桶数组记录
	}
	for(int i=1;i<=n;i++){
		b[i].x=n-1+ton[a[i].y];//记录穿主队服的次数
		b[i].y=n-1-ton[a[i].y];//记录穿客队服的次数
	} 
	for(int i=1;i<=n;i++)
		cout<<b[i].x<<" "<<b[i].y<<endl;
	return 0;
}
```


---

## 作者：GCSG01 (赞：1)

## 思路
利用桶数组储存冲突的球服，每只队伍都会比 $n$ 场，如果别人的队服与自己相同，穿主队服的场数就加上冲突队伍数，穿客队服场数的计算同理。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int z[100005],c[100005],t[100005];//t为桶数组
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>z[i]>>c[i],t[z[i]]++;//主队服冲突
	for(int i=1;i<=n;i++)
		cout<<n+t[c[i]]-1<<" "<<n-t[c[i]]-1<<endl;
  //n+t[c[i]]-1:n为必穿主队服的场数，t[c[i]]-1为冲突场数，-1是因为不能包含自己。n-t[c[i]]-1同理。
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

[**题目传送~~**](https://www.luogu.com.cn/problem/CF432B)

题目讲的已经很清楚了，所以直接讲思路。

***思路：***

那既然是 $n$ 个球队打比赛，求出穿主球队服和客球队服，那我们可以直接模拟，***解释见代码***。

***Code：***

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define re ra()

const int N=1e4+5;

int n,x[N],y[N],s1,s2;
inline int ra()
{
	int jjy=0,txy=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') txy=-1;ch=getchar();}
	while(isdigit(ch)){jjy=jjy*10+ch-'0';ch=getchar();}
	return jjy*txy;
}//快读
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=re;
	for(int i=1;i<=n;i++) x[i]=re,y[i]=re;
	for(int i=1;i<=n;i++)//直接模拟
	{
		s1=s2=0;//清0，因为有n个球队，不清0就会重复计算（s1表示穿主队服的次数，s2表示穿客队服的次数）
		for(int j=1;j<=n;j++)
		{
			if(i==j) continue;//自己和自己比显然是不可能的，所以跳过
			if(y[i]==x[j]) s1++;//如果第i各球队的客队服与第j个球队的主队服一样，那么第i个球队就穿自己的主队服
			else s2++;
		}
		printf("%lld %lld\n",s1+n-1,s2);//因为每个球队都会打n-1场比赛，所以就会穿n-1次主队服
	}
	return 0;
}
```

~~完结撒花！~~

~~嗯，怎么超时了！！~~

注意看题目，$n \le 10^5$，那么双重循环肯定做不了。那应该怎么办呢？？？

~~经过两年半的~~思考，我们可以用桶来做。

我们只需要记录每个球队的主队服，然后在用个一重循环，输出就行了。

***Code：***

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define re ra()

const int N=2e5+5;

int n,a[N],x[N],y[N],s1,s2;

inline int ra()
{
	int jjy=0,txy=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') txy=-1;ch=getchar();}
	while(isdigit(ch)){jjy=jjy*10+ch-'0';ch=getchar();}
	return jjy*txy;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=re;
	for(int i=1;i<=n;i++) 
	{
		x[i]=re,y[i]=re;
		a[x[i]]++;
	}
	for(int i=1;i<=n;i++)
		printf("%lld %lld\n",a[y[i]]+n-1,n-1-a[y[i]]);//n-1上面已经解释过了
	return 0;
}
```

完结撒花！！！

~~点个赞再走呗！~~

---

## 作者：tmz2011 (赞：1)

# 题意

有 $A$，$B$ 两支球队，分别有主队服和客队服。

当客队和主队队服相同时认为冲突，客队换成自己主队的队服。

求每个队伍主队服穿了几次，客队服穿了几次。

# 思路

顺向思维推到。

1.记录主队服出现的次。

2.求出冲突次数。

3.输出穿主队服次数和穿客队服的次数。

# 代码

```cpp
#include <bits/stdc++.h> 
using namespace std;

int n,a[100100] = {0},b[100100] = {0},c[100100] = {0};

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i] >> b[i];
        c[a[i]]++;
    }
    for (int i = 0; i < n; i++)
        cout << n - 1 + c[b[i]] << " " << n - 1 - c[b[i]]<< endl;
        //因为要减掉一场自己是主场，所以n要减一。
    return 0;
}

```

---

## 作者：pengbubu (赞：0)

## 题意
从题目可以知道：我们需要判断所有球队队服的重复情况。重复后客队球衣数量减去一。
## 思路
总的来说有两种思路。一种是**二分**（从时间复杂度来说确实可以实现），但是码量相对较多。第二种是采取**直接统计重复**，这也是我的方法。

我们可以使用 map 和数组（相当于桶）来实现。这两种代码仅有声明部分不同(代码会附注释)。

主场和客场有 $(n-1)$ 场。所以，主场队服数量为场数加上重复球衣数量；客场队服数量为场数减去重复球衣数量。故，套用此公式直接输出即可（这应该很好理解吧）。
## 代码

```cpp
#include<bits/stdc++.h>
#define MAXN 100005 //最大值 
using namespace std;
int n, home, away; 
//用map: map<int , int> cnt;——余下代码一样的 
int x[MAXN], y[MAXN], cnt[MAXN];
int main(){
	scanf("%d",&n);//队伍数量 
	for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]), cnt[x[i]]++;//cnt专门存重复情况 
	for(int i=1;i<=n;i++){
		home = n-1+cnt[y[i]];//主场：home
	//  主场衣服初始值（n-1）次，如果后面重复，加上重复的次数即可——即为（n-1+cnt[y[i]]） 
		away = n-1-cnt[y[i]];//客场反之 
		printf("%d %d\n",home,away);//打印 
	}
	return 0;
}
```

---

## 作者：zhouzihang1 (赞：0)

# CF432B Football Kit 题解

## 题意

给出 $n$ 支球队的主场队服种类和客场队服种类。

对于队伍 $i,j$，将进行两场比赛：

- 队伍 $i$ 主场对阵队伍 $j$。

- 队伍 $j$ 主场对阵队伍 $i$。

所以比赛将共进行 $n \times (n-1)$ 场。

其中对于主场队伍，其队服种类为其主场队服。

对于客场队伍，若其客场队服与主场队伍的主场队服种类相同，则将使用**主场**队服，否则使用**客场**队服。

数据范围：

$1 \le N \le 2 \times 10^5, 1 \le V \le 10^6$。

$a_i \neq b_i$。

## 思路

注意到一支队伍会进行 $2n - 2$ 场比赛，其中主场和客场分别进行 $n-1$ 场比赛。

所以对于当前球队，我们只需要计算有多少场比赛是**客场**参加，且当前球队的客场队服与其他球队的主场队服种类相同，记为 $tmp$，答案即为 $n - 1 + tmp$ 和 $n - 1 - tmp$。

对于有多少球队主场队服与当前球队客场队服种类相同，可以使用桶记录。

## AC Code

[link](https://codeforces.com/problemset/submission/432/277642561)

---

## 作者：liyp (赞：0)

## 解题思路
这题可以用桶来记录冲突的球服（当然用 ``map`` 也可以）。

在题目中，每支球队都会比赛 $n$ 场。对于每一场比赛，如果两支队伍的队服相同，那么穿主队服的场数**就加上冲突的队伍数**，穿客队服场数就是主队场次数去加上有多少队的主队服与当前客队服**重复**。

## 部分代码（参考）
### 计算 + 输出
```cpp
cout << flag[k[i]] + n - 1 << " " << n - 1 - flag[k[i]];
// i 是指第几支客队。
```

## 完整代码
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN = 1e5 + 10;
int z[MAXN], k[MAXN];
int flag[MAXN];
signed main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> z[i] >> k[i];
		flag[z[i]]++;
	}
	for (int i = 1; i <= n; i++) {
		cout << flag[k[i]] + n - 1 << " " << n - 1 - flag[k[i]];
		cout << endl;
	}
	return 0;
}

```

---

## 作者：WhxStar2024 (赞：0)

## 本题思路：
这道题其实并不复杂，我们只需要用到桶去暴力枚举即可。

我们可以先用桶记录每个主队的队服数量，然后我们可以发现不论如何只要在主场主队就都会穿主队的队服，切在客场时只要与他队的主队队服冲突就会换回主服，那么穿主队队服的次数就是主场次数去加上有多少队的主服与我们的客服重复。

那么客队队服就更好算了，我们只用在客场的次数减去重复的次数即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
struct f{
	int x,y;
}b[100001],ans[100001];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>b[i].x>>b[i].y;
		a[b[i].x]++;
	}
	for(int i=1;i<=n;i++)
	{
		cout<<n+a[b[i].y]-1<<" "<<n-1-a[b[i].y]<<endl;
	}
	return 0;
}
```


---

## 作者：_Violet_Evergarden (赞：0)

看到题解有些空缺，来发一发。

# 思路
我们首先读完题意后发现只要主队与客队的颜色冲突，那么客队穿主队衣服的次数就会加 $1$，然后考虑我们只需要将主队的颜色用桶储存下来就可以拿下了。

# 题解
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int x[100001];
int y[100001];
int zhu[100001];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		zhu[x[i]]++;
	}
	for(int i=1;i<=n;i++){
		cout<<(n-1)+zhu[y[i]]<<" "<<(n-1)-zhu[y[i]]<<endl;
	}
	return 0;
}
```


---

## 作者：SunsetVoice (赞：0)

更新：修改了没写完的部分（有句号了）。

## 解法

极好的思维题。

首先考虑暴力。枚举每一场比赛，计算冲突数量。时间复杂度 $O(n^2)$，数据范围 $n \le 10^6$，总计算量 $10^{12}$，成功炸飞。

首先注意到一共要比赛 $n\times(n+1)$ 场，也就是说**每两个球队之间要比赛 $2$ 场**。

考虑预处理出使用每种球衣的球队总数。即使用第 $i$ 种球衣的队为 $b_i$ 个。

对于每一个球队，其使用主队球衣的次数为其主场数加上客场中冲突的数量。而其使用其使用客队球衣的比赛数量为其客场数减去客场中冲突的数量。

每个队要和 $n-1$ 个队比赛 $2$ 次，主场一次，客场一次。


```cpp
#include<bits/stdc++.h>
using namespace std;
int a1[1000001] = {0},a2[1000001] = {0},b[1000001] = {0};
int main(){
	int n;
	cin>>n;
	for(int i = 1;i<=n;i++){
		cin>>a1[i]>>a2[i];
		b[a1[i]]++;
	}
	for(int i = 1;i<=n;i++){
		cout<<n+b[a2[i]]-1<<" "<<n-b[a2[i]]-1<<endl;
	}
	return 0;
}
```



---

## 作者：J_Kobe (赞：0)

### 题意
其中两队比赛时客队和主队队服相同视为一次冲突，客队就会换成自己主队的队服。按顺序输出每个队伍主队服穿了几次，客队服穿了几次。

### 思路
首先当一队为主场时，是不会换队服的，所以我们只需要统计这个队的客场队服与多少个队的主场队服一样就行了，这里我们可以用桶将主场队服的个数记录下来。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int x[100005], y[100005];
int t[100005];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &x[i], &y[i]);
		t[x[i]]++; // 用来统计主场队服的出现次数
	}
	for (int i = 1; i <= n; i++)
	{
		printf("%d %d\n", n-1+t[y[i]],n-1-t[y[i]]); // 分别为主场队服和客场队服的出现次数
	}
	return 0;
}
```

---

## 作者：hard_learn (赞：0)

# 题意

计算 $n$ 支球队在 $n(n-1)$ 场比赛中穿主队和客队服的次数，同色则客队换主队服。输出每队的主客场穿着次数。

# 思路
- 读取队伍总数 $n$。

- 循环读取每场比赛的主队和客队编号，统计每个队伍分别作为主队和客队的比赛次数。

- 对于每场比赛，计算并输出主队和客队的比赛场次。

- 注意不能跟自己打比赛。

# 代码如下
```
#include<bits/stdc++.h>
using namespace std;
int n;
int x[100005],y[100005];
int sum[100005];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		sum[x[i]]++;
	}	
	for(int i=1;i<=n;i++){
		cout<<n+sum[y[i]]-1<<" ";//主队 
		cout<<n-sum[y[i]]-1<<endl;//客队 
	}
	return 0;
} 
```

---

## 作者：The_jester_from_Lst (赞：0)

枚举带个桶。

题面讲得十分清楚，于是我们首先想到 $O(n^2)$ 枚举，一一判断。然而当我们看向英文题面，发现 $n$ 会到 $10^5$ 次。于是我们考虑用桶优化，引入 $t_i$ 表示以 $i$ 为主场队服的球队个数。显然有第 $i$ 只球队穿主场队服的次数为 $t_i+n-1$（$n-1$ 为在自己主场比赛的次数，显然自己的主场穿自己的主场球衣），客场队服就是 $n-1+t_i$ 次。

附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
inline int rd(){
	int jya=0,tl=1;char jyt=getchar();
	while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
	while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
	return jya*tl;
}
inline void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
int n,zhu[200086],ke[200086],t[200086];
signed main(){
	n=rd();
	for(int i=1;i<=n;++i)zhu[i]=rd(),ke[i]=rd(),++t[zhu[i]];
	for(int i=1;i<=n;++i){
		wr(n-1+t[ke[i]]);
		putchar(' ');
		wr(n-1-t[ke[i]]);
		putchar('\n');
	}
	return 0;
}
```


---

