# [CEOI 2005] Multi-key Sorting

## 题目描述

考虑一个包含行和列的表。列从 $1$ 到 $C$ 编号。为简单起见，表中的项目是由小写字母组成的字符串。  
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/z70sexo1.png)  
您将获得对此类表的 Sort($k$) 操作：Sort($k$) 按照列 $k$ 中的值的顺序对表的行进行排序（而列的顺序不会改变）。排序是稳定的，即在第 $k$ 列中具有相等值的行保持其原始顺序。例如，将 Sort($2$) 应用于表 $1$ 会产生表 $2$。  
我们对此类排序操作的序列感兴趣。这些操作依次应用于同一个表。例如，应用序列 Sort($2$)；Sort($1$) 到表 $1$ 产生表 $3$。  
如果两个排序操作序列对于任何表具有相同的效果，则它们被称为等效。例如，Sort($2$)；Sort($2$)；Sort($1$) 等效于 Sort($2$)；Sort($1$)。但是，它不等效于 Sort($1$)；Sort($2$)，因为对表 $1$ 的影响不同。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 \leq C \leq 10^6$，$1 \leq N \leq 3×10^6$，$1 \leq k_i \leq C$。  
#### 题目说明  
来源于 CENTRAL-EUROPEAN OLYMPIAD IN INFORMATICS 2005 的 Multi-key Sorting。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
4 6
1 2 1 2 3 3```

### 输出

```
3
1 2 3```

# 题解

## 作者：Aybbl_xc (赞：4)

# 前言
本蒟蒻的第一篇题解，跟一位大佬思路一样，~~一道很水的题~~
# 题目大意
题目有点难理解，多读几遍就能通

大概就是找有多少个不同数字，接着输出个数，和最后一次出现的顺序输出
# 分析
**看到这道题就能想到桶排，再看眼范围只有 $\displaystyle10^6$ 所以先记录个数，再遍历一遍，注意最后要倒序输出**

# 接下来直接看代码
```
#include<bits/stdc++.h>
using namespace std;
int m,n,ans,temp;
int gs[1000001];//用来记录个数 
int a[1000001],sum[1000001];//答案数组 
bool b[1000001];//用来统计 
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		gs[a[i]]++;
	}
	for(int i=1;i<=1000000;i++){//从题中得知最大为1000000 
		if(gs[i]) ans++;
	}
	for(int i=n;i>=1;i--){//题目说倒着第一个出现
	    if(b[a[i]]!=true){
	    	sum[++temp]=a[i];
	    	b[a[i]]=true;//标记已访问 
		}else continue; 
	}
	cout<<ans<<endl;//输出个数
	for(int i=ans;i>=1;i--) cout<<sum[i]<<" "; 
	return 0;//好习惯 
}
```
完结散花！！！

希望管理员能过


---

## 作者：2021sunzishan (赞：2)

这题的题目的意思很难懂，不过本蒟蒻在看完大佬的题解后茅塞顿开！

##### ~~其实 $c$ 在题目当中一点用没有呵呵。~~


### 题目大意：
 给定一个长度为 $n$ 的序列，求有多少个不同数字，并按照最后一次出现的顺序输出。
 
### 思路：
1. 开一个桶记录每个数出现的次数。
2. 把桶遍历一遍，求数的个数。
3. 再按读入顺序从后往前遍历一遍。
    - 如果这个数已经在之前遍历过了，即不是最后一次出现的，就跳过。
    - 否则，是最后一次出现，将这个数记录进答案数组中。
    
- 注意：答案数组中存储的数是输出结果的倒序，相当于是一个栈。

4. 最后倒序输出答案。



如果还是看不懂，就看代码吧！

### 切勿抄袭！！！
```c
#include <bits/stdc++.h>
using namespace std;
bool vis[1000005];
int vis1[1000005],a[1000005],n,c,s=0,ans[1000005];
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>c>>n;
	for (int i=1; i<=n; i++) {
		cin>>a[i];
		vis1[a[i]]++; //统计每个数出现多少次 
	}
	for (int i=1; i<=1000000; i++) {
		if (vis1[i])
			s++; //统计一共有几个数 
	}
	int s1=0;
	cout<<s<<'\n'; //先输出数的个数 
	for (int i=n; i>=1; i--) { //注意，是按照最后一次的出现顺序 
		if(!vis[a[i]]) { //如果这个数还没有被访问到 
			ans[++s1]=a[i]; //用ans数组记录下来 
			vis[a[i]]=1; //这个数标记为已访问 
		} else
			continue; //如果已经访问过了，就跳过 
	}
	for (int i=s; i>=1; i--) { //必须要倒过来输出 
		cout<<ans[i]<<' '; 
	}
	return 0;
}

```

完结~

---

## 作者：Gumbo (赞：2)

本题是一道略有思维难度的新手好题，总体实现不难，但思想有些复杂。

我们来看题面：

>有一个长度为 `N` 的序列，其中的每个元素有 `C` 个关键字，我们将依次进行多次 __稳定__ 的单关键字排序，找到最短的一个等效排序方法。

我们来分析这样一个性质：

>当你进行了一次排序时，之前的一切相同排序都没有意义。

显而易见， __稳定__ 排序具有 __幂等性__ （即重复操作不影响结果，具体可以去看ST表相关知识），因此本性质是正确的。

那么这道题目的思路也就出来了：

>对于每一种排序，我们只保留最后一次。

本题解完。

---

附：最优解、最短解代码。

```cpp
#include<cstdio>
using namespace std;
int lst[1000006];
int num[3000006];
int main(){
    int c,n;
    scanf("%d%d",&c,&n);
    int ans=0;
    for(int i=1;i<=n;++i){
        scanf("%d",&num[i]);
        if(lst[num[i]]==0)++ans;
        lst[num[i]]=i;
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;++i)if(lst[num[i]]==i)printf("%d ",num[i]);
    return 0;
}
```

`lst` 数组：这个值对应的最后一次出现位置。

`ans`：不同的值个数（显然，每个值保留一个，那么最短的操作长度就是不同类型排序的种类数），也就是最短操作长度。

思路：输入时判断是否第一次出现并处理 `ans`，输出时判断是不是最后一个并输出。

__完__


---

## 作者：auto_iterator (赞：2)

#### [题目传送门](https://www.luogu.com.cn/problem/P7686)
## part . 1 分析题意
第一眼看到这道题的时候顿时懵，后来看了看两位题解大大的思路后顿时理解，自己随手写了几组发现是对的，于是立刻开打，调了一下就过了

 其实这个题还是比较简单的，

 简单来说，就是先计算出有多少个数（去重），
 
 再分别倒序找到这几个数最后出现的地方，
 
 最后按照它们最后出现的顺序输出这几个数（注意这里是正着输出）。
 
 很容易想到桶，看一眼数据发现可行，下面的输出开始我使用的栈，但是爆了，改成数组就可以了。

## part .2 讲解做法
用一个桶，算出去重后还剩几个数，

再用一个 ```int``` 类型数组存一下最后出现的顺序，

然后用一个 ```bool``` 型的 ```vis``` 数组判断是否都出现过了，

最后再倒过来输出即可。
## part . 3 
## AC Code
```
#include<bits/stdc++.h>
using namespace std;
int tot=1;//计数
bool vis[10101010];//标记
int bot[10101010];//桶
int stl[10101010]; //存数.1
int c,n;
int x;
int y=0;
int stl1[10101010];//存数.2
int main(){
	cin >> c >> n;
	for(int i=1;i<=n;i++)//读入
	{
		cin >> x;
		bot[x]++;
		stl[i]=x;
	}
	for(int i=0;i<1000100;i++)
	{
		if(bot[i]!=0)
		{
			y++;//计算有多少个数
		}
	}
	cout << y<<endl;
	for(int i=n;i>=1;i--)//倒序查找
	{
		if(vis[stl[i]]==0)
		{
			stl1[tot]=stl[i];
			tot++;
			vis[stl[i]]=1;
		}
		else continue;
	}
	for(int i=y;i>=1;i--)
	{
		cout << stl1[i]<<' ';//输出
	}
	return 0;
}
```



---

## 作者：fish_shit (赞：1)

# 题目大意

~~这道题的题面真的不是人能看的。~~

总的来说，它是让你解决两个问题

$1$：找出序列中有多少个不同的数字。

$2$：按照每个数字最后输入的下标位置的顺序输出每个数字。

# 实现方法

很简单，只需要借助桶数组模拟就行了。如果一个数第一次出现就标记一下，未标记的数就代表是第一次出现，标记过的数就代表以前出现过了。可以借用这种方法解决本题。

详细看代码。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int a[maxn],b[maxn],cnt,pos,c,n;
bool tong1[maxn],tong2[maxn];
int main(){
	cin>>c>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(!tong1[a[i]]){ 
			cnt++;//统计不同的数字个数
			tong1[a[i]]=1;
		}
	}
	cout<<cnt<<endl;
	for(int i=n;i>=1;i--){
		if(!tong2[a[i]]){
			b[++pos]=a[i];//将第一次出现的数字计入数组 
			tong2[a[i]]=1;
		}
	}
	for(int i=pos;i>=1;i--){//注意最后要倒序输出 
		cout<<b[i]<<" ";
	}
	return 0;
}
```
望管理员大大通过！

---

## 作者：icaijy (赞：1)

可能是空间最小的题解，只开了一个大小为 $10^6$ 的 `bool` 数组，最终占用空间为 $4.1$ MB，因为后来用到了栈导致空间依没那么小。
# 题意
这题最难的是读题，这题题面真是比较阴间。翻译成人类的语言是这样的。

给你一个长度为 $n$ 的数组，你需要求出这个**数组里有多少个不同的数**，并且**按照每个数字最晚出现的位置的顺序输出每一个数**。

题目里还有个 $c$，代表着数组里只会出现 $1$ 到 $c$ 的数，不过对我们做题没用。

如果你还没看懂（~~那可能是我说的比较绕~~），那么结合样例看一下。

```
4 6
1 2 1 2 3 3

    1 2   3
    最最   最
    后后   后
    的的   的
    位位   位
    置置   置
```
首先肯定要先输出 $3$，因为这个数组里只出现了 $1,2,3$ 三个数。
接下来，我在下面标注了每个数最后出现的位置。从第一个数出现的最后位置（这里是 $1$），一直输出到最后一个（也就是 $3$）就行了。

# 实现
对于第一小问，用一个变量 `ans` 记录答案。读入的时候用一个布尔数组记录一下有没有出现，如果**读入了一个没有出现的数**的话，就标记一下，然后 `ans++`。

对于第二小问，首先每个数读入到一个栈。因为我选择从**后往前扫**，这样**扫到的第一个数就是这个数最后一次出现的位置**。用栈先入后出的特性正好合适。因为从后往前扫，所以要逆序输出。这样把每次扫到第一次出现的数存到一个栈，还是用先入后出的特性就可以输出了。

# 代码
说了那么多，代码其实很简单，觉得前面看不太懂得看注释就行了。
```cpp
#include <iostream>
#include <stack>// 栈
#include <cstring>// memset
using namespace std;
bool a[1000005];

int main(){
    int c,n,ans=0;
    cin >> c >> n;
    int k;
    stack<int> s;
    for (int i=0;i<n;i++){
        scanf("%d",&k);
        if (!a[k]) ans++; // 新的数，ans++
        s.push(k);
        a[k]=true;
    }
    cout<<ans<<endl;
    memset(a,false,sizeof(a)); // 节约空间，重置一下，用来记录接下来是不是第一次
    int countt=0;// 
    stack<int> s2;
    while (countt!=ans){ // 如果数全部扫完了
        if (!a[s.top()]) s2.push(s.top()),a[s.top()]=true,countt++; // 第一次出现就压进s2
        s.pop();
    }
    while (!s2.empty()) printf("%d ",s2.top()),s2.pop(); // 输出
}

```

---

## 作者：happybob (赞：1)

远古 CEOI 题。

## 题意

题意我一直没看懂，但是我发现这道题其实是将一个序列中所有相同的数字只保留一个，若多个相同则保留最靠近序列末尾的一个。

接着将保留的序列逆序输出即可。

## 解法

考虑记录数组 `vis`，表示某个数是否出现过。因为要保留末端，所以逆序遍历即可。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int N = 1e6 + 5;

bool vis[N];
int n, a[N], cnt = 0;
vector<int> ans;

int main()
{
	scanf("%*d%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	for (int i = n; i >= 1; i--)
	{
		if (!vis[a[i]])
		{
			cnt++;
			vis[a[i]] = true;
		}
	}
	printf("%d\n", cnt);
	memset(vis, false, sizeof(vis));
	for (int i = n; i >= 1; i--)
	{
		if (!vis[a[i]])
		{
			ans.push_back(a[i]);
			vis[a[i]] = true;
		}
	}
	reverse(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}
```


---

## 作者：szh_AK_all (赞：0)

[传送门](https://www.luogu.com.cn/problem/P7686)

## 题目大意（加分析）
这道题还是挺简单的，题意就是让我们输入一串数字，然后将它化简。化简的方法是：记录每个数字最后一次出现的位置，按照位置先后将它们输出来。这还是很好解决的，我们只要用一个桶来记录就行了。
# Code
```c
#include<iostream>
using namespace std;
int s[1000005],a[1000005],p[1000005],o=0;
int main()
{
    int c,n;
    cin>>c>>n;
    for(int i=1;i<=n;i++)
        cin>>s[i];
    for(int i=n;i>=1;i--)//注意，这里是从后往前，因为是要记录每个数字最后一次出现的顺序
    {
    a[s[i]]++;
    if(a[s[i]]==1)
    p[++o]=s[i];
    }
    cout<<o<<endl;
    for(int i=o;i>=1;i--)//从后往前
    cout<<p[i]<<" ";
    return 0;
}
```
大家注意，顺序问题一定不能出错，下面是我第一次提交代码，就是因为没注意顺序，只得了 $6$ 分（呜呜）。
```c
#include<iostream>
using namespace std;
int a[1000005],p[1000005],o=0;
int main()
{
    int c,n;
    cin>>c>>n;
    for(int i=1;i<=n;i++)//不排序的下场
    {
        int x;
        cin>>x;
        a[x]++;
        if(a[x]==1)
        p[++o]=x;
    }
    cout<<o<<endl;
    for(int i=1;i<=o;i++)
    cout<<p[i]<<" ";
    return 0;
}
```


---

## 作者：_Evergarden_ (赞：0)



------------------
### [原题链接](https://www.luogu.com.cn/problem/P7686)


## ~~一道十分考验人类阅读能力的题。~~


------------


## 题目大意

第一部分：求出有多少种数字；

第二部分：求出每一种数字最后一次出现的地方（顺序）。

- 对于第一部分，可以使用桶排，将每一种数字存储下来。

- 对于第二部分，使用倒序枚举，若这个数没有出现过，就存进数组中；若已经出现过，就跳过。

## 算法实现

首先用一个数组 $b$ 存储数字，并且对于每一种数字都用计数器 $ans$ 记录下来；

其次，再用数组 $l$ 存储每一种数字最后一次出现的顺序，再用数组 $b$ 标记下来。

## 注意：$b$ 数组要清零，~~别问我怎么知道的。~~



------------


### 下面附上代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int c, n, a[N], b[N], ans, l[N], cnt;//cnt控制下标

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);//读入优化
    cin >> c >> n;
    for(int i = 1; i <= n; ++ i) {
        cin >> a[i];
        b[a[i]] ++;//数字加1
    }
    for(int i = 1; i <= 1000000; ++ i) {//循环枚举
        if(b[i] != 0) ans++;//若在里面存了数，则数的种类加1
    }
    cout << ans << "\n";
    memset(b, 0, sizeof b);//清零
    for(int i = n; i >= 1; -- i) {//倒序枚举
        if(!b[a[i]]) {//若此时里面未存储数，就说明这是第一个出现的数
            l[++cnt] = a[i];//存储进去
            b[a[i]] = 1;//标记一下
        }
        else {//若已经有了
            continue;//就返回
        }
    }
    for(int i = cnt; i >= 1; -- i) {//倒序输出
        cout << l[i] << " ";
    }
    return 0;
}
```


---

## 作者：songhx (赞：0)

### 题意：

非常的晦涩，读了好几遍才明白过来。

简要题意：给定一个长度为 $n$，由 $1,2,3,……,c$ 组成的序列（ $1$ 到 $c$ 不一定都出现过），将它去重后输出它的项数，然后按照每个元素在原数列中最后一次出现的下标（最靠后的一个）从前向后输出。

### 解法：

看到 $C$ 的范围比 $N$ 小，第一想法肯定是桶。

因为后期需要对桶进行排序，下标就不能表示该元素的值，所以考虑使用结构体。

桶里面存储的是元素最后在原数列中出现的位置（下标），初始化为 $0$。

输入序列不需要存入数组，只需要把下标存进桶里就可以了。

接着，用 sort 函数按照最后出现的下标由小到大排序。

输出时注意，如果桶里某个元素第一个出现的下标显示为 $0$，即在输入序列时并没有输入过该元素，那么不输出。

# ACcode:

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

struct node{
	int x,d; //x是元素值，d是最后出现的下标
}a[1000005];

bool cmp(node a,node b){
	return a.d < b.d;
}

int main(int argc, char *argv[]) {
	int c,n;
	cin >> c >> n;
	for(int i = 1; i <= c; i++) {
		a[i].x = i;
		a[i].d = 0; //d初始化为0
	}
	int m = 0;
	for(int i = 1; i <= n; i++){
		int tmp; //序列里的元素
		cin >> tmp;
		if(a[tmp].d == 0) m++; //如果d=0，即该元素在序列里第一次出现，那么去重后的数组必然包括tmp
		a[tmp].d = i; //记录d
	}
	sort(a + 1, a + c + 1,cmp); //排序，按照d的大小
	cout << m << endl;
	for(int i = 1; i <= c; i++) if(a[i].d != 0) cout << a[i].x << ' ';
	return 0;
}
```


---

