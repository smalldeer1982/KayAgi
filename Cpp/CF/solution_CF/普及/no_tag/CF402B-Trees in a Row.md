# Trees in a Row

## 题目描述

## 题意
有$n$个正整数，可以对一个数进行修改(修改后也是正整数)，要求修改之后满足$a_i+k=a_{i+1}$,求最少的修改次数以及具体的修改方案

## 样例 #1

### 输入

```
4 1
1 2 1 5
```

### 输出

```
2
+ 3 2
- 4 1
```

## 样例 #2

### 输入

```
4 1
1 2 3 4
```

### 输出

```
0
```

# 题解

## 作者：ycy1124 (赞：17)

### 题意
有一个数列 $a$ ，我们要将他变成一个公差为 $k$ 的 **等差数列** ，每次可以将数列中的一个数更改成 **任意另外一个正整数** ，求最少的操作次数与操作方案。

### 想法
已知它是一个等差数列，假设我们知道其中的一个位置上的一个数，我们就一定可以求出整个等差数列。

于是，问题变成了确定 $a$ 其中的一个整数，使其它的数所需要的变化次数最少。

### 做法
假如两个数确定后他们的首项相同，那么他们两个必定是在 **同一个** 公差为 $k$ 等差数列中的，因此我们可以将它们的首项统计起来，最后取统计次数最多的来还原整个等差数列。

之所以统计首项，是因为这个数列必定是 **单调递增** 的。如果它的首项为正数，数列中的所有数也必定是正数。

所以我们只需要在边输入时边用一个桶去计数。

数列中的数必须是正数，所以首项 $\le0$ 的无需统计。

### 代码
下面为大家提供了两份代码：

+ $\mathcal{O}(n\log n)$ 的排序做法。
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001];
struct Node{
	int w;
	long long i;//结构体计数与存储首项。
}t[1001];
bool cmp(Node x1,Node x2){//自定义排序。
	return x1.w>x2.w;
}
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		t[max(a[i]-k*(i-1),0)].w++;//统计首项。
		t[max(a[i]-k*(i-1),0)].i=max(a[i]-k*(i-1),0);//记录他的首项方便还原数列
	}
	sort(t+1,t+1001,cmp);//排序。
	if(n-t[1].w==0){//无用的特判。
		cout<<0;
		return 0;
	}
	printf("%d\n",n-t[1].w);//输出操作次数。
	for(int i=1;i<=n;i++){//还原数列，输出答案。
		if(t[1].i+k*(i-1)>a[i]){
			printf("+ %d %lld\n",i,t[1].i+k*(i-1)-a[i]);
		}
		else if(t[1].i+k*(i-1)<a[i]){
			printf("- %d %lld\n",i,abs(t[1].i+k*(i-1)-a[i]));
		}
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/168886601)。

+ $\mathcal{O}(N)$ 的边输入，边统计做法。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001];
struct Node{
	int w;
	long long i;
}t[10001];
int main(){
	int n,k;
	int js1=0,js2=0;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		t[max(a[i]-k*(i-1),0)].w++;
		if(t[max(a[i]-k*(i-1),0)].w>js1&&max(a[i]-k*(i-1),0)!=0){//与排序不同，是直接统计出现最多的首项。
			js1=t[max(a[i]-k*(i-1),0)].w;
			js2=max(a[i]-k*(i-1),0);
		}
		t[max(a[i]-k*(i-1),0)].i=max(a[i]-k*(i-1),0);
	}
	if(n-t[1].w==0){
		cout<<0;
		return 0;
	}
	printf("%d\n",n-t[js2].w);
	for(int i=1;i<=n;i++){
		if(t[js2].i+k*(i-1)>a[i]){
			printf("+ %d %lld\n",i,t[js2].i+k*(i-1)-a[i]);
		}
		else if(t[js2].i+k*(i-1)<a[i]){
			printf("- %d %lld\n",i,abs(t[js2].i+k*(i-1)-a[i]));
		}
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/168886054)。

---

## 作者：chlchl (赞：9)

## 题目意思
题目翻译得非常清楚，在具体点来说就是给定一个长度为 $n$ 的数列，每次操作可以把其中一个数变成任意一个正整数。求最小操作次数 $ans$，使得这个数列成为一个公差为 $k$ 的递增等差数列。

## 做法
本题为一道暴力模拟题。

很容易注意到 $n\leq 1000$，数据范围出奇的小，所以暴力枚举每一棵树 $a_i$ 高度不变的情况。

对于每个 $a_i$，我们求出其他树现在应达到的高度 $a1_i$，求出变换数量 $cnt$。接着，如果 $ans < cnt$，则更新答案，同时用结构体 $s$ 存下每一步的信息，最后输出即可。

## 一些小坑
- 求 $a1$ 数组时，需要将当前不变的那棵树的高度事先存进数组里。
- 每次记得把 $a1$ 数组清零（定义在循环里也行）。
- 每棵树的高度必须是正整数，如果求出某一棵树的应有高度小于等于 $0$（不是小于 $0$），就要直接退出循环，找下一棵树。（没注意的话第 $36$ 个点是红的）。
- 输出时注意符号与编号之间有空格！
- $ans$ 的初值赋无穷大，大概 $10^5$ 左右就够了。

## 代码
以下代码仅供参考，珍爱生命，远离抄袭。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1000 + 10;
int n, k, ans = 100000, a1[N], a[N];
//ans要赋无穷大（1e5够了） 
struct step{
	char ch;
	int idx, value;
} s[N];
//结构体 

int main(){
	cin >> n >> k;
	for(int i=1;i<=n;i++)	cin >> a[i];
	for(int i=1;i<=n;i++){
		bool flag = false;//判断是否有非正整数 
		memset(a1, 0, sizeof(a1));//数组清零 
		int cnt = 0;
		a1[i] = a[i];//第 i 棵树不变，应有高度自然就是 a[i] 
		for(int j=i+1;j<=n;j++)	a1[j] = a1[j - 1] + k;//求出 i 后树的应有高度（等差数列） 
		for(int j=i-1;j>=1;j--){//求出 i 前树的应有高度（等差数列） 
			a1[j] = a1[j + 1] - k;
			if(a1[j] <= 0){//加不会≤0，但是减可能会，这里要判断 
				flag = true;
				break;
			}
		}
		if(flag)	continue;//考验质量的时候到了！！ 
		for(int j=1;j<=n;j++)	if(a1[j] != a[j])	cnt++;//过关了，统计操作次数 
		if(cnt < ans){
			int k = 0;
			ans = cnt;//更新答案 
			for(int j=1;j<=n;j++){
				if(a1[j] == a[j])	continue;//一样的不用记录 
				else if(a1[j] > a[j]){
					s[++k].ch = '+', s[k].idx = j, s[k].value = a1[j] - a[j];//记录每次操作，不用清零，可以直接覆盖 
				}else{
					s[++k].ch = '-', s[k].idx = j, s[k].value = a[j] - a1[j];//同上 
				}
			}
		}
	}
	cout << ans << endl;
	for(int i=1;i<=ans;i++){
		cout << s[i].ch << ' ' << s[i].idx << ' ' << s[i].value << endl;//注意输出格式！！ 
	}
	return 0;//下班 
}
```
本篇题解到此结束，如果对你有帮助别忘了点个赞哦！

---

## 作者：_maple_leaf_ (赞：2)

### [luogu](https://www.luogu.com.cn/problem/CF402B) [CF](http://codeforces.com/problemset/problem/402/B)

## 思路
这题直接 $O(n^2)$ 暴力就好了，只要枚举每一个位置，以当前位置作为基准，向前向后修改一遍，统计更改次数，与答案比较，统计答案输出就好了，不需要太多脑子，具体见代码。
## code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	char c=getchar();
	int ret=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		ret=(ret<<3)+(ret<<1)+c-'0';
		c=getchar();
	}return ret*f;
}
inline void write(int x,int op){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10,0);
	putchar((char)(x%10+'0'));
	if(op){
		if(op>0)puts("");
		if(op<0)putchar(' ');
		if(op==0)puts("114514");
	}
}
const int N=1e3+10;
int n,k;
int a[N];
struct node{
	char c;
	int id,x;
}an[N],ann[N];
int cnt,ans=114514;
int b[N];
bool cmp(node x,node y){//对操作顺序排序
	return x.id<y.id;
}
signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)b[i]=read();//正常输入
	for(int st=1;st<=n;st++){
		memset(an,0,sizeof an);//清空临时答案数组
		cnt=0;//清空临时操作次数
		for(int i=1;i<=n;i++)a[i]=b[i];//复制原数组
		for(int i=st+1;i<=n;i++){//往后修改
			if(a[i]!=a[i-1]+k){
				int tmp=(a[i-1]+k)-a[i];//算差
				an[++cnt].c=(tmp>0?'+':'-');//记录正负
				an[cnt].id=i;//记录操作位置
				an[cnt].x=abs(tmp);//记录操作数
				a[i]=a[i-1]+k;//改变当前值
			}
		}
		for(int i=st-1;i>=1;i--){//往前修改
			if(a[i]!=a[i+1]-k){
				if(a[i+1]-k<=0){//以防过边界
					cnt=114514;
					break;
				}
				int tmp=a[i+1]-k-a[i];//如往后修改
				an[++cnt].c=(tmp>0?'+':'-');
				an[cnt].id=i;
				an[cnt].x=abs(tmp);
				a[i]=a[i+1]-k;
			}
		}
		if(cnt<ans){//统计答案
			ans=cnt;
			for(int i=1;i<=cnt;i++)ann[i]=an[i];
		}
	}
	sort(ann+1,ann+1+ans,cmp);//排序
	write(ans,1);//正常输出
	for(int i=1;i<=ans;i++){
		putchar(ann[i].c);
		putchar(' ');
		write(ann[i].id,-1);
		write(ann[i].x,1);
	}
	return 0;
}//~*完结撒花*~
```

---

## 作者：xxxalq (赞：2)

[洛谷链接](https://www.luogu.com.cn/problem/CF402B) & [CF链接](http://codeforces.com/problemset/problem/402/B)

## 思路分析：

不妨先观察一下数据范围：$1\le n\le 1000$，所以大概就是要 $O(n^2)$ 的时间复杂度，那么我们可以枚举一个基准点，再计算以这个点为基准每个点需要如何操作。

定义一个 $dp$ 数组，$dp_{i,j}$ 表示以 $a_i$ 为基准，$a_j$ 需要加上多少，当然如果要减，$dp_{i,j}$ 就为负数。

因为这道题不是动态规划，所以没有状态转移方程。

注意：因为这是树的高度，所以不能为负数，要特判，可以自己再翻译一下原题面。

## 代码：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,k,a[1010],dp[1010][1010],idx,minn=0x3f3f3f3f;//切记dp只是数组名，minn要赋极大值记录最小操作次数
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		int tmp=0;//记录当前操作次数
		bool flag=false;//特判0
		for(int j=1;j<=n;j++){
			int x;
			if(i==j){
				continue;//当前无需修改
			}
			if(i<j){
				x=a[i]+(j-i)*k-a[j];//计算要加多少
				if(x!=0){//如果要修改
					dp[i][j]=x;//就修改
					tmp+=1;//次数加一
				}
			}else if(i>j){
				x=a[i]-(i-j)*k-a[j];//计算要加多少
				if(a[j]+x<=0){//如果减到非正数
					flag=true;//标记
					break;
				}
				if(x!=0){//如果要修改
					dp[i][j]=x;//就修改
					tmp+=1;//次数加一
				}
			}
		}
		if(tmp<minn&&!flag){//更新最小值
			minn=tmp;//更新最小值
			idx=i;//最小值基准下标
		}	
	}
	cout<<minn<<endl;
	for(int i=1;i<=n;i++){
		int x=dp[idx][i];
		if(!x){
			continue;//无需修改
		}
		if(x>0){
			cout<<"+ "<<i<<" "<<x;
		}else{
			cout<<"- "<<i<<" "<<-x;
		}
		cout<<endl;//换行
	}
	return 0;
}
```


---

## 作者：Alice2012 (赞：2)

有点小坑但不难想的题目。

## 思路

看到 $1\leq n,k\leq 1000$ 时就已经很明了了。直接暴力枚举每个 $a_i$ 不变的情况，求出当 $a_i$ 不变时数列的取值。对于求出的每种数列，计算其代价并使用 `vector` 记录其操作。最后输出最小的代价及代价最小的操作形式。

## 坑点

要求改变后的数列每个数为正整数，所以要特判当某个元素不是正整数时，当前 $a_i$ 不变的情况不合法。

- 作者刚开始没看题，没有判断正整数，WA on #6。

- 作者发现问题后急火攻心，将判断正整数判断成了判断非负整数，WA on #36。

特此警示。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+5;
int n,k,ans=1e9,posi;
int a[N];
struct node{
	char op;
	int pos,x;
};
vector<node>v[N];
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++){//a[i]不变的序列 
		int bas=a[i],cnt=0,flg=0;
		for(int j=1;j<=n;j++){
			//a[i]不变时a[j]的取值:bas-k*(i-j) 
			if(bas-k*(i-j)<=0){
				flg=1;
				break;
			}
			if(a[j]!=bas-k*(i-j)){//不同 
				cnt++;//修改次数+1 
				if(bas-k*(i-j)<a[j])
					v[i].push_back({'-',j,a[j]-(bas-k*(i-j))});
				else
					v[i].push_back({'+',j,(bas-k*(i-j))-a[j]});
				//存入操作 
			}
		}
		if(cnt<ans&&!flg)//记录答案 
			ans=cnt,posi=i;
	}
	cout<<ans<<"\n";
	for(int i=0;i<v[posi].size();i++)//输出 
		cout<<v[posi][i].op<<" "<<v[posi][i].pos<<" "<<v[posi][i].x<<"\n";
	return 0;
}
```

---

## 作者：Tachibana27 (赞：2)

给定一个序列 $a$，希望你用最少的修改次数，使得其变成一个公差为 $k$ 的等差数列。

注意到 $n$ 不是很大，可以跑到 $O(n^2)$ 甚至以上。若确定首项及公差则可以推出全序列。不妨暴力枚举首项的值并推出等差数列，若原序列的第 $i$ 位 $a_i$ 与等差数列的第 $i$ 位 $b_i$ 不同，则当前位置需要修改。答案取需要修改的次数的最小值。

推出第一个答案后，具体的操作是可以确定的。具体的，再次暴力枚举首项，若需要修改的次数与先前得出的答案一样则找到了操作原序列的方法。若当前位置为 $i$，$a_i<b_i$ 则加，反之则减。

特别的，可能会有多种最优解，故输出一次最优解后应当终止程序。

code:

```cpp
int a[100086];
int tst[100086];
int n,k;
int qwq;
int ans=INT_MAX;
int main(){
    std::cin>>n>>k;
    for(int i=1;i<=n;i++)
        std::cin>>a[i];
    for(int i=1;i<=1086;i++){//枚举首项
        tst[1]=i;//首项
        qwq=0;
        for(int j=2;j<=n;j++)
            tst[j]=tst[j-1]+k;//推出等差数列
        for(int j=1;j<=n;j++)
            if(a[j]!=tst[j])
                qwq++;//需要修改的次数
        ans=std::min(ans,qwq);
    }
    std::cout<<ans<<"\n";//答案一
    for(int i=1;i<=1086;i++){
        tst[1]=i;
        qwq=0;
        for(int j=2;j<=n;j++)
            tst[j]=tst[j-1]+k;//同上，枚举首项并推出等差序列
        for(int j=1;j<=n;j++)
            if(a[j]!=tst[j])
                qwq++;
        if(qwq==ans){//若当前为最优解
            for(int j=1;j<=n;j++)
                if(a[j]!=tst[j])
                    if(a[j]<tst[j])
                        std::cout<<"+ "<<j<<" "<<tst[j]-a[j]<<"\n";
                    else
                        std::cout<<"- "<<j<<" "<<a[j]-tst[j]<<"\n";//输出答案，
            exit(0);//找到最优解后则终止程序，撒花！
        }
    }
}
```

---

## 作者：mnlbnkk (赞：1)

# 题目意思
给你一个 $n$ 个元素的数列 $a$，和一个数 $k$ 要你做到用最少的调整次数把 $a$ 变成一个公差为 $k$ 的等差数列，并给出方案。
# 思路
不难想到 $a_i$ 之和 $a_1$ 与 $k$ 有关，所以可以尝试枚举 $a_1$，发现 $n$ 和 $a_i$ 的值域都特别小，所以我们可以直接枚举 $a_1$ 的值，时间复杂度可过。
# Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
const ll N=1e3+9;
ll n,a[N],k,b[N],ans=-INF,ft;
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=10000;i++)
    {
        b[1]=i;
        for(int j=2;j<=n;j++)
            b[j]=b[j-1]+k;
        ll sum=0;
        for(int j=1;j<=n;j++)
            if(a[j]==b[j])
                sum++;
        if(sum>ans)
            ans=sum,ft=i;
    }
    cout<<n-ans<<endl;
    for(int i=1;i<=n;i++)
        if(a[i]!=ft+(i-1)*k)
        {
            ll tmp=ft+(i-1)*k;
            if(tmp>a[i])
                cout<<"+ "<<i<<" "<<tmp-a[i]<<endl;
            else cout<<"- "<<i<<' '<<a[i]-tmp<<endl;
        }
    return 0;
}
```

---

## 作者：Z_AuTwT (赞：1)

## 题意

给你一个序列和一个整数，你可以任意修改序列中的数，使得
这个序列为1一个等差数列且公差为给出的那个整数。

## 思路

我们可以将这个数列中的任意一个数钦定为最后的等差数列中的一个数，这样我们就可以求出这个数列中的每一项，然后逐一比较统计答案即可。

## CODE

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long//其实没必要
int arr[1010];
struct C{
	char fh;
	int id,z;
}Arr[1010],Brr[1010];//Arr用于存储答案，Brr用于在单次中记录答案
bool Cmp(C a,C b){
	return a.id<b.id;
}
main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>arr[i];
	int minn=1e9;
	for(int i=1;i<=n;i++){
		int dt1=arr[i]-(i-1)*k;//求出首项
		if(dt1<=0) continue;//题目要求：不能为非正整数
		int cnt=0;
		for(int j=1;j<=n;j++){//对于每项逐一判断
			if(arr[j]!=dt1){
				cnt++;
				Brr[cnt].id=j;
				Brr[cnt].fh=(arr[j]>dt1?'-':'+');
				Brr[cnt].z=abs(arr[j]-dt1);
			}
			dt1+=k;
		}
		if(cnt<minn){
			minn=cnt;
			for(int i=1;i<=cnt;i++){
				Arr[i]=Brr[i];
			}
		}
	}
	cout<<minn<<"\n";
	for(int i=1;i<=minn;i++) cout<<Arr[i].fh<<" "<<Arr[i].id<<" "<<Arr[i].z<<"\n";
}
```

---

## 作者：aCssen (赞：1)

### Solution
因为题目要求修改后每个 $a_i$ 都满足 $a_i+k=a_{i+1}$，所以满足条件的数列一定是一个公差为 $k$ 的等差数列。

注意到 $a_i,n \le 1000$，所以我们可以每举每个可能的 $a_1$，进而推出整个数列，分别计算出答案，再比较一下即可。时间复杂度 $O(1000n)$，可以通过本题。
### 一些细节
+ 计数器每次都要清零。
+ 答案初始化为一个大数。
+ 注意输出格式。

### 代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=1005;
int num[maxn],judge[maxn],n,k,tot,ans=1e9;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&num[i]);
	for(int i=1;i<=1000;i++){
		judge[1]=i;//设置首项为i
		tot=0;
		for(int j=2;j<=n;j++)
			judge[j]=judge[j-1]+k;//推出整个数列
		for(int j=1;j<=n;j++)
			if(num[j]!=judge[j]) tot++;//对于每个不相等的值，花费一次操作使其相等
		ans=min(ans,tot);//更新答案
	}
	printf("%d\n",ans);
	for(int i=1;i<=1000;i++){
		judge[1]=i;
		tot=0;
		for(int j=2;j<=n;j++)
			judge[j]=judge[j-1]+k;
		for(int j=1;j<=n;j++)
			if(num[j]!=judge[j]) tot++;//同上
		if(tot==ans){//是最优解
			for(int j=1;j<=n;j++){
				if(num[j]!=judge[j]){
					if(num[j]<judge[j]) printf("+ %d %d\n",j,judge[j]-num[j]);
					else printf("- %d %d\n",j,num[j]-judge[j]);//注意输出格式
				}
			}
			return 0;//可能有多组解，但应只输出一种，所以要结束程序
		}
	}
	return 0;
}
```
[无注释版](https://www.luogu.com.cn/paste/o8i6sag7)

---

## 作者：minVan (赞：1)

**解题思路**

对于一个等差数列，取决于首项 $a_1$ 和公差 $k$。

$k$ 已经给出了，所以我们直接暴力枚举首项 $b_1\in[1,1000]$，再将 $b_i=b_1+k\times(i-1)$ 与 $a_i$ 进行对比即可。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1005;
int n, d, a[N], mini = 1e9, b[N];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> d;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for(int j = 1; j < N; j++) {
    int t = 0;
    for(int i = 1; i <= n; i++) {
      if(a[i] != j + d * (i - 1)) {
        ++t;
      }
    }
    if(t < mini) {
      mini = t;
      for(int i = 1; i <= n; i++) {
        b[i] = j + d * (i - 1);
      }
    }
  }
  cout << mini << '\n';
  for(int i = 1; i <= n; i++) {
    if(a[i] < b[i]) {
      cout << "+ " << i << " " << b[i] - a[i] << '\n';
    }
    if(a[i] > b[i]) {
      cout << "- " << i << " " << a[i] - b[i] << '\n';
    }
  }
  return 0;
}
```

---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF402B)

这道题目可以使用暴力来解（细节不少，调了我半个多小时）。

我们来看一下这道题，数据范围是 $n\le 1000$。而我们的暴力时间复杂度是 $O(n^2)$ 如果常数不是特别大，可以使用。

我们需要枚举如果第 $i$ 个数不变的情况下变化的次数，然后求一下最小值。

这里注意，题目少翻译了一点，：

> 对于所有的数，不论是调整前，还是调整后。在任何时候都**不能小于等于** $0$。（注意这里的符号）

那么，我们怎么解决这个问题呢？

很简单，只需要把当前变化的次数变的特别大，就行了。这样是进入我们正常的判断时，这个答案一定不会采纳。当然，设一个特殊值（比如 $-1$）也是可以的。

在这里提供一个样例：

输入：

```
3 1
1 1 2
```
输出：

```
2
+ 2 1
+ 3 1
```

我们最后需要输出一下方案，怎么输出？

我们只需要到底是第几个常数不变，才能让我们变化的次数最小就行了，然后最后再判断一遍到底是加还是减。

---
# AC代码
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int num[1005],a[1005],b[1005],n,k,total,minn=1e5,place;
bool yes=1;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&num[i]);
	minn=1e5;
	for(int i=1;i<=n&&yes;i++){
		yes=1;//其实这个yes没什么用
		total=0;
		memset(b,0,sizeof(b));
		b[i]=num[i];
		for(int j=i-1;j>=1;j--){
			b[j]=b[j+1]-k;
			if(b[j]<=0){
				total=1e9;//设置一个超大的答案
				break;//退出循环
			}
		}
		for(int j=i+1;j<=n;j++){
			b[j]=b[j-1]+k;
			if(b[j]<=0){
				total=1e9;
				break;
			}
		}
		for(int j=1;j<=n;j++){
			if(b[j]!=num[j])total++;//如果不等，次数加1
		}
		if(minn>total)place=i;//保留当前数
		minn=min(minn,total);//取最小值
 	}
	printf("%d\n",minn);
	if(minn==0)return 0;
	a[place]=num[place];
	for(int j=place-1;j>=1;j--)a[j]=a[j+1]-k;
	for(int j=place+1;j<=n;j++)a[j]=a[j-1]+k;
	for(int i=1;i<=n;i++){
		if(a[i]>num[i])printf("+ %d %d\n",i,a[i]-num[i]);
		if(a[i]<num[i])printf("- %d %d\n",i,num[i]-a[i]);
	}
	return 0;
}
```


---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF402B)

一道枚举题。

数据范围非常小，考虑暴力枚举。枚举第一棵树的高度，如果按照这样排列需要的操作次数是**最小的**，就选用这棵树作为新的第一棵树的高度，然后求出剩下的树的高度。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n, k, maxn = -INF, maxl = -INF, top, q; // top 是新的第一个高度
int a[1005], b[1005];
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        maxn = max(maxn, a[i]); // 只需要枚举到最大值
    }
    for (int i = 1; i <= maxn; i++) {
        int cnt = i, sum = 0; // sum 是统计以 i 这个高度为开头有多少棵树不用进行操作
        if (i == a[1]) sum++; 
        for (int j = 2; j <= n; j++) {
            cnt += k;
            if (cnt == a[j]) sum++;
        }
        if (sum > maxl) { // 最多有多少棵树不操作
            maxl = sum;
            top = i;
        }
    }
    b[1] = top;
    int x = top + k;
    for (int i = 2; i <= n; i++) {
        b[i] = x;
        x += k;
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] != b[i]) q++;
    }
    cout << q << "\n";
    for (int i = 1; i <= n; i++) {
        if (a[i] < b[i]) cout << "+ " << i << " " << b[i] - a[i] << "\n";    
        if (a[i] > b[i]) cout << "- " << i << " " << a[i] - b[i] << "\n";
    }
    return 0;
}



```


---

## 作者：_HiKou_ (赞：0)

可以看到数据范围灰常的小，$1\le n,k\le 1000$，所以可以考虑对于每一个数，枚举以这个数为基准的等差数列。（不可能全部改掉，一定有一个可以留下的）（比如说这个数是 $a$，那么它的上一个数为 $a-k$，下一个数为 $a+k$，以此类推。）

但是有一点要注意的是数的高度为正整数，所以要先判断这个序列的第一个数（序列单调递增，判断第一个即可）是不是正整数。如果不是直接退出。

还有，在判断一个序列时如果碰到 $a_i=b_i$ 的情况，可以考虑标记起来。易挣这两个数做基准的序列一定是一样的。（可以自己想想）

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans=114514,i,j,ast=0;//ast 存作为基准数的数
int a[1145],vis[1145];
int main(){
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	int now=0;
	for(i=1;i<=n;i++)
	{
		now=0;//需改动的数量
		if(vis[i])continue;//判断
		vis[i]=1;
		if(a[i]-k*(i-1)<=0)continue;//判断正整数
		for(j=i-1;j>=1;j--)//向前求数列
		{
			int wt=a[i]-(i-j)*k;
			if(wt!=a[j])now++;
			else vis[a[j]]=1;
		}
		for(j=i+1;j<=n;j++)//同理向后求
		{
			int wt=a[i]+(j-i)*k;
			if(wt!=a[j])now++;
			else vis[a[j]]=1;
		}
		if(ans>=now)//最小值
		{
			ans=now;
			ast=i;
		}
	}
	printf("%d\n",ans);
	int nf=a[ast]-k*(ast-1);//第一个数
	for(i=1;i<=n;i++)//修改
	{
		if(a[i]!=nf)
		{
			if(a[i]<nf)printf("+ %d %d\n",i,(nf-a[i]));
			else printf("- %d %d\n",i,(a[i]-nf));	
		}
		nf+=k;
	}
	return 0;
} 
```

---

## 作者：rfsfreffr (赞：0)

这道题木有表面上的那么简单，交了好几次才过。

我一开始，以为是直接从$a_1$开始将数列推出，但是后来我看到要求输出的是最优解，所以我就意识到，从任意一个$a_i$开始将数列推出也是合法的。又看到数据较小(n<=1000)可以直接暴力将每种可能算出来，再求最优解。

最后还有一点需要注意，这些树的高度必须是正整数。

直觉告诉我应该又比$O(n^2)$更优的算法，但是我还没有想到。

所以这里就直接献上$O(n^2)$的暴力做法吧



# 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int a[100001];
int b[100001];
int f[1001],ans=1e9,l;
int main(){
    cin>>n>>k;
    for(int i=1; i<=n; i++) scanf("%d",&a[i]);
    for(int i=1; i<=n; i++){
        b[i]=a[i];//选择基准数
        for(int j=1; j<=n; j++){//求出数列
            if(j<i) b[j]=b[i]-k*(i-j);
            else b[j]=b[i]+k*(j-i); 
            if(b[j]<=0) goto mmp;//如果有负数，直接跳出去
            
        }
        for(int j=1; j<=n; j++){//计算要修改几次
            if(a[j]!=b[j]) {
                f[i]++;
            }
        }
        if(f[i]<ans){//记录答案
            ans=f[i];
            l=i;
        }
mmp:
		1;
    }
    b[l]=a[l];//选择最优基准
    cout<<ans<<endl;//输出答案
    for(int j=1; j<=n; j++){//求出数列
        if(j<l) b[j]=b[l]-k*(l-j);
        else b[j]=b[l]+k*(j-l); 
    }
    for(int i=1; i<=n; i++){//按题意输出
        if(a[i]>b[i]){
            printf("- %d %d\n",i,a[i]-b[i]);
        } else if(a[i]<b[i])printf("+ %d %d\n",i,b[i]-a[i]);
    }
    return 0;
} 
```

---

## 作者：eros1on (赞：0)

**真 · 水黑**

乍一看题没啥思路

但注意题目中各种数据都在 1000 以内啊。。

这不就模拟了么。。

由于 $a \leq 1000$ ，所以只需要暴力枚举 $b$ 就行啦（如下）

$b_1 \in [1,1000]$

然后就没什么好说的了

算一下修改次数，更新最小值就行了

```cpp
#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
typedef long long ll;
const int N = 1000 + 100;    // change N   here
const int inf = 0x3f3f3f3f; // change inf here

inline int rd() {
  int s = 0, w = 1; char c = getchar();
  while (c < '0' || c > '9') { if (c == '-') w = -1; c = getchar(); }
  while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
  return s * w;
}

int n, k, a[N], b[N], ans, c[N], d[N];

int main() {
  n = rd(), k = rd(); ans = inf;
  rep(i, 1, n) a[i] = rd();
  rep(i, 1, 1000) {
    int sum = 0;
    b[1] = i; // 枚举 b[1]
    rep(j, 2, n) b[j] = b[j - 1] + k; // 由 b[1] 推出 b[i]
    rep(j, 1, n) {
      c[j] = b[j] - a[j]; // 算出差
      if (c[j]) sum++; // 统计修改次数
    }
    if (ans > sum) { // 更新答案
      rep(j, 1, n) d[j] = c[j];
      ans = sum;
    }
  }
  printf("%d\n", ans);
  rep(i, 1, n) {
    if (!d[i]) continue ;
    if (d[i] > 0) printf("+ %d %d\n", i, d[i]);
    else printf("- %d %d\n", i, -d[i]);
  }
  return 0;
}
```

---

## 作者：HDWR (赞：0)

本文同步发布于[Handwer's Blog](https://blog.handwer-std.top/)

---

~~先说点题外话~~

这道题是我今天（发题解的那一天，2019.08.07）打 ACM 的时候做的，当时看到这题口胡了一下做法，没敢写，交给队友去写了，然后一遍AC

感谢队友把我带飞

---

言归正传。

考虑枚举第一棵树的高度，因为这样就能直接确定后面的树的高度了 

然后假设当前枚举第一棵树高度为 $l$，那么第 $i$ 棵树的高度 $h_i$ 就应该是 $l + k(i - 1)$，这个应该很好理解吧，如果不懂可以评论区留个言，我找个时间写一下

那么再套一层循环，枚举所有的树，如果当前枚举到的第 $i$ 棵树的高度不是 $l + k(i - 1)$，就意味着这棵树需要被修改，需要增高 / 降低的高度是 $\text{abs}(l - k(i - 1))$，需要增高还是降低取决于 $l - k(i - 1)$ 的符号

统计一下修改了多少次，作为一个方案，最后取一个最优方案的输出就行了

---

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

#define FILE_IN(__fname) freopen(__fname, "r", stdin)
#define FILE_OUT(__fname) freopen(__fname, "w", stdout)
#define rap(a,s,t,i) for (int a = s; a <= t; a += i)
#define basketball(a,t,s,i) for (int a = t; a > s; a -= i)
#define countdown(s) while (s --> 0)
#define IMPROVE_IO() std::ios::sync_with_stdio(false)

using std::cin;
using std::cout;
using std::endl;

typedef long long int lli;

int getint() { int x; scanf("%d", &x); return x; }
lli getll() { long long int x; scanf("%lld", &x); return x; }

const int MAXNKH = 1000 + 10; // the max of n, k, height
const int LOC = 0;
const int MODIFY = 1;

int n, k, ans = 0x7f7f7f7f, ansf[MAXNKH][2], p, f[MAXNKH][2];
int height[MAXNKH];

int main() {
    n = getint(); k = getint();
    rap (i, 1, n, 1) height[i] = getint();
    rap (h1, 1, 1000, 1) {
        // 枚举第一棵树的高度，可以直接确定后面树的高度
        p = 0; memset(f, 0, sizeof f);
        rap (i, 1, n, 1) {
            if (height[i] - (i - 1) * k != h1) {
            	// 记一下要修改的树的下标和要增加 / 减少的值
                f[++p][LOC] = i;
                f[p][MODIFY] = (h1 + (i - 1) * k) - height[i];
            }
        }
        if (p < ans) {
            // 更优的方案，更新一下
            ans = p;
            memcpy(ansf, f, sizeof f);
        }
    }
    printf("%d\n", ans);
    rap (i, 1, ans, 1) printf("%c %d %d\n", (ansf[i][MODIFY] < 0 ? '-' : '+'), ansf[i][LOC], std::abs(ansf[i][MODIFY]));
    return 0;
}

// Code by Handwer
```

---

## 作者：Cold_Eyes_bystander (赞：0)

我们暴力确定数列的起点，计算出最小的代价，特判最小代价是 $n$ 的情况，让 $a_{1}$ 不变就行了。

时间复杂度是平方级别，不会超时。

```c++
#include <bits/stdc++.h>
#define int long long 
using namespace std;
int a[19198100];
 main()
{
	int n;
	int k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	int minn=1e9,minnid;
	for(int i=-k+1;i<=n;i++)
	{
		int sum=i,cnt=0;
		for(int i=1;i<=n;i++)
		{
			sum+=k;
			if(a[i]!=sum) cnt++;
		}
		if(minn>cnt)
		{
			minn=cnt,minnid=i;
		}
	}
	if(minn==n)
	{
		minnid=a[1]-k;
		minn--;
	}
	cout<<minn<<endl;
	int sum=minnid,cnt=0;
	for(int i=1;i<=n;i++)
	{
		sum+=k;
		if(a[i]>sum)
		{
			cout<<"- "<<i<<" "<<a[i]-sum<<endl;
		} 
		if(sum>a[i])
		{
			cout<<"+ "<<i<<" "<<sum-a[i]<<endl;
		}
	}
	return 0;
}
```

---

## 作者：z_yq (赞：0)

### 题目意思
给出两个正整数 $n$，$k$ 和一个序列 $a$，每次你可以更改 $a$ 序列中的任意一个数的值，求要多少次操作可以让 $a$ 变为一个公差为 $k$ 的等差数列，且满足 $1 \le a_i \le 1000$。

### 思路
因为 $a_i$ 的数据范围很小，所以我们可以枚举首项，我们就可以推出整个序列，然后推出与原序列不一样的数量，取最小值即可。

时间复杂度：枚举 $a_i$ 花费 $\mathcal{O(a_i)}$ 枚举正给序列也是 $\mathcal{O(n)}$ 整体复杂度 $\mathcal{O(a_i \times n)}$ 可以通过

### Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
const ll N=1e3+9;
ll n,a[N],k,b[N],ans=-INF,ft;
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=10000;i++)
    {
        b[1]=i;
        for(int j=2;j<=n;j++)
            b[j]=b[j-1]+k;
        ll sum=0;
        for(int j=1;j<=n;j++)
            if(a[j]==b[j])
                sum++;
        if(sum>ans)
            ans=sum,ft=i;
    }
    cout<<n-ans<<endl;
    for(int i=1;i<=n;i++)
        if(a[i]!=ft+(i-1)*k)
        {
            ll tmp=ft+(i-1)*k;
            if(tmp>a[i])
                cout<<"+ "<<i<<" "<<tmp-a[i]<<endl;
            else cout<<"- "<<i<<' '<<a[i]-tmp<<endl;
        }
    return 0;
}
```

---

## 作者：20111019Yu (赞：0)

### 题意
给定一个长度为 $n$ 的序列 $a$，求最少更改几次元素后序列变为公差为 $k$ 的[等差数列](https://baike.baidu.com/item/%E7%AD%89%E5%B7%AE%E6%95%B0%E5%88%97/1129192)。
### 思路
因为 $1\leq a_{i}\leq1000$ 所以直接暴力枚举 $a_{1}$，求每次修改次数的最小值。
### code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k, a[10005], minn = 1e9, id;

signed main(){
	cin >> n >> k;
	for( int i = 1; i <= n; i++ ) cin >> a[i];
	for( int i = 1; i <= 1000; i++ ){
		int sum = i, lin = 0;
		for( int j = 1; j <= n; j++ ){
			if(sum != a[j]) lin++;
			sum += k; 
		}
		if(lin < minn){
			minn = lin;
			id = i;
		} 
	}
	cout << minn << '\n';
	for( int i = 1; i <= n; i++ ){
		if(a[i] != id){
			if(a[i] > id){
				printf("- %lld %lld\n", i, abs(a[i] - id));
			}
			else{
				printf("+ %lld %lld\n", i, abs(id - a[i])); 
			}
		}
		id += k;
	}
	return 0;
}
```

---

## 作者：YangXiaopei (赞：0)

## Solution

我们可以发现 $n$ 的范围很小，只到 $1000$，足以满足 $O(n^ 2)$ 级别的算法。

我们枚举每个数，以这个数不变，作公差为 $k$ 的等差数列。

再把这个等差数列与原数组对比，记录不同的个数，即为答案。

要注意几个坑：

* 树的高度为正，一旦构造出的等差数列中有非正数，跳出。否则在会卡在第 $36$ 个点（我在这里卡了半天啊啊啊）。

* $ans$ 初值不为 $0$，比 $n$ 大一点即可。

## 核心代码：

```cpp
int cnt = 0, f = 0;
memset(b, 0, sizeof(b));
b[i] = a[i];
for(int j = i + 1; j <= n; j++){
	b[j] = b[j - 1] + k;
	if(b[j] <= 0){
		f = 1;
		break;
	}
}
for(int j = i - 1; j >= 1; j--){
	b[j] = b[j + 1] - k;
	if(b[j] <= 0){
		f = 1;
		break;
	}
}
if(f){
	continue;
}
for(int j = 1; j <= n; j++){
	if(b[j] != a[j]){
		cnt++;
	}
}
```

---

## 作者：huyangmu (赞：0)

注意到 $n\le1000$，所以可以想到 $n^2$ 暴力枚举。

根据贪心的思想，如果每个数都要进行修改需要 $n$ 次操作，所以考虑固定一个 $a_{i}$，根据 $a_{i}$ 对其余的数进行操作，这样最多只会操作 $n-1$ 次，比把每个数都改一遍更优。

所以考虑枚举每一个不变量 $a_{i}$ 通过 $a_{i}$ 计算前面和后面的数，如果和原来的值相等，就不用进行操作，同时记录最小操作次数，并记录此时 $i$ 的值。最后用一个结构体统计每个数的信息即可，时间复杂度 $O(n^2)$，可以通过。

要注意，修改后每个 $a_{i}$ 都要是正整数。

### AC Code


```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 1e3 + 5;
int n, k, a[N], b[N], cnt, ans = LONG_LONG_MAX, pos, sum;
struct node{
	char c;
	int x, val;
}c[N];
bool cmp (node x, node y){
	return x.x < y.x;
}
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i){
		cin >> a[i];
		b[i] = a[i];	
	}
	for (int i = 1; i <= n; ++i){
		if (a[i] - (i - 1) * k <= 0) continue;
		for (int j = 1; j <= n; ++j) b[j] = a[j];
		int cnt = 0;
		for (int j = i - 1; j >= 1; --j){
			b[j] = b[j + 1] - k;
			if (b[j] != a[j]) ++cnt;
		}
		for (int j = i + 1; j <= n; ++j){
			b[j] = b[j - 1] + k;
			if (b[j] != a[j]) ++cnt;
		}
		if (ans > cnt){
			ans = cnt;
			pos = i;
		}
	}
	cout << ans << '\n';
	for (int i = 1; i <= n; ++i) b[i] = a[i];
	for (int i = pos - 1; i >= 1; --i){
		b[i] = b[i + 1] - k;
		if (b[i] != a[i]){
			if (b[i] < a[i]) {
				++sum;
				c[sum].c = '-';
				c[sum].x = i;
				c[sum].val = a[i] - b[i];
			}
			else{
				++sum;
				c[sum].c = '+';
				c[sum].x = i;
				c[sum].val = b[i] - a[i];
			}
		}
	}
	for (int i = pos + 1; i <= n; ++i){
		b[i] = b[i - 1] + k;
		if (b[i] != a[i]){
			if (b[i] < a[i]) {
				++sum;
				c[sum].c = '-';
				c[sum].x = i;
				c[sum].val = a[i] - b[i];
			}
			else{
				++sum;
				c[sum].c = '+';
				c[sum].x = i;
				c[sum].val = b[i] - a[i];
			}
		}
	}
	sort (c + 1, c + sum + 1, cmp);
	for (int i = 1; i <= sum; ++i) cout << c[i].c << ' ' << c[i].x << ' ' << c[i].val << '\n';
	return 0;
}

---

