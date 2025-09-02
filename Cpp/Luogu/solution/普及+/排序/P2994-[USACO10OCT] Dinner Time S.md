# [USACO10OCT] Dinner Time S

## 题目描述

农场主约翰的 $N$（$1 \le N \le 10 ^ 3$）头奶牛被编号为 $1 \sim N$，它们正在保加利亚参加 IOI。奶牛们喜欢保加利亚的太阳并享受着它们的假日，一切看起来都没问题。

变化发生在晚餐时间前后。这家餐馆很小，只有 $M$（$1 \le M \le N$）个座位，编号为 $1 \sim M$。每头牛从一个位置 $CX_i$，$CY_i$ 进入餐馆（$-10 ^ 6 \le CX_i \le 10 ^ 6,-10 ^ 6 \le CY_i \le 10 ^ 6$）；座位可以在 $SX_j$，$SY_j$ 找到（$-10 ^ 6 \le SX_j \le10 ^ 6,-10 ^ 6\le SY_j\le 10 ^ 6$）。



奶牛有一种非常有效的（尽管很原始）方法把自己分配到座位上。一旦某只奶牛确定她会先到某个座位上，她就会尽快赶到那里（所有的奶牛都跑得一样快）。



农场主约翰的奶牛和所有获奖的奶牛一样，跳过座位、桌子或其他奶牛都没有问题，因此它们可以直线奔跑。当多头牛可以同时到达一个座位时，最老的牛（在输入数据中出现得更早的牛）获得座位。当一头牛可以第一个到达多个座位时，她也会选择在输入中最早出现的座位。



一些奶牛将不能吃晚饭，这些吃不到饭的饥饿的奶牛正集体计划偷农场主约翰自己的食物。农场主约翰想要一份他应该提防的奶牛名单。（如果没有饥饿的奶牛，则输出 $0$）。你能帮他吗？



注：在计算中可能会有超过 $32$ 位整数范围但在 $64$ 位整数范围内的数。

------------

## 样例 #1

### 输入

```
2 1 
0 1 
1 0 
1 10 
```

### 输出

```
2 
```

# 题解

## 作者：yinhy09 (赞：5)

### 理解题意：
我第一次看这道题的时候，没理解输入数据，所以在这里解释一下:

题目中的奶牛进入餐厅和座位的四个变量，两两一组是直角坐标系里的 $X,Y$ 轴
因为这个题最多 $1000\times1000$（$m,n\leq1000$ )所以直接暴力枚举！

那么问题又来了，到底先枚举奶牛还是座位。也就是两层循环哪一个放在外面
当然是先枚举座位，即外层循环是枚举座位，内层循环枚举奶牛。因为每一个奶牛不一定有座位，但是每一个座位一定有奶牛。


本题可以定义四个数组储存变量，但是这里可以优化一下，只定义两个数组，剩下两个直接定义成普通变量。因为座位可以每输入一个进行一次奶牛查找（判断哪一个奶牛）放在同一个 `for` 循环中，具体见下方代码:



### 代码示例：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000+5;//为了方便定义数组，直接把数据范围控制好
long long a[maxn],b[maxn],c,d;//a,b表示奶牛计入房间位置，c,d表示座位位置
int flag[maxn];//用来标记那些奶牛已经有座位了
int pos;//记录有座位的奶牛编号
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i]>>b[i];
	for(int j=1;j<=m;j++)
	{
		cin>>c>>d;
		long long dis=0;//计算当前奶牛到座位的距离，用勾股定理（因为只需要比较，所以没有开根号）
		long long mindis=1e15;//记录当前最小奶牛距桌子距离（开始随便赋值，大一些）
		for(int i=1;i<=n;i++)
		{
			if(flag[i]==1)continue;//已有座位，直接跳过
			dis=(a[i]-c)*(a[i]-c)+(b[i]-d)*(b[i]-d);//计算距离，用勾股定理
			if(dis<mindis)//如果刷新了最小纪录
			{
				mindis=dis;//重新赋最小值
				pos=i;//标记
			}
		}
		flag[pos]=1;//标记，已有座位
	}
	if(n==m)//特判没有奶牛无座位
	{
		cout<<0;
		return 0;
	}
	for(int i=1;i<=n;i++)//其他情况输出
	{
		if(flag[i])continue;
		cout<<i<<endl;
	}
	return 0;
}

```


---

## 作者：nofind (赞：4)

菜鸡的第一篇题解，请无聊刷完水题之后随便逛逛题解区的大佬见谅。
先来说说这道题：~~语文神题~~。 反正我第一眼看蒙了。~


------------

那么简单说下题意：

就是给你一些初始坐标，还有一些座位的坐标，每头牛见草眼开，开始抢座位，先到先得（题目说成是老牛~~可能老牛被安排离桌子近~~），牛会优先抢先输入的桌子。最后问你编号为几的牛分不到座位。

其实就是道纯暴力枚举。
上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,ans;
ll cx[1001],cy[1001],sx[1001],sy[1001];//存坐标的数组 
bool match[1001];
ll d(ll x1,ll y1,ll x2,ll y2)//计算距离 
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>cx[i]>>cy[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>sx[i]>>sy[i];
	}
	for(int i=1;i<=m;i++)//枚举座位
	{
		ll min=5810925546507845,t;//数据范围稍大，我开了long long  
		for(int j=1;j<=n;j++)//枚举每一头牛 
		{
			if(!match[j])//如果牛没被“安排 ”了~ 
			{
			
				ll dis=d(cx[j],cy[j],sx[i],sy[i]);//计算牛离当前桌子距离 
				if(dis<min)//如果它比其他牛先到就更新 
				{
					min=dis;
					t=j;
				}
			}
		}
		match[t]=1;//给它打上标记 
	}
	bool flag=0;//记录是否有牛分不到座位（其实一上来判断n与m即可，我懒得写~~） 
	for(int i=1;i<=n;i++)
	{
		if(!match[i])
		{
			flag=1;
			cout<<i<<endl;
		}
	}
	if(!flag)
	{
		cout<<0;
	}
	return 0;
}
```

---

## 作者：hyc1026 (赞：1)

本题比较明显，可以用贪心来做。

注意数据范围，要开 long long。

### 首先我们来看一下题意简述。

- 给一些牛的初始坐标，和桌椅的坐标。
- 对于题目说，奶牛可以跳过其它奶牛和桌椅，这点不用在程序中体现（可以理解为席地而坐）。
- 牛会抢先输入的桌子，而更老的牛会比更年轻的牛具有更多优先权。
- 问编号为几的牛无法抢到桌椅？
- 不开 long long 见祖宗。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;

long long cx[1001], cy[1001], sx, sy, flag[1001];
long long mindis, dis, pos; //注意开long long。
//cx,cy,sx,sy记录奶牛的坐标和座位的坐标

int main()
{
    int n,m;
    cin >> n >> m;
    for(int i=1; i<=n; i++)
    {
        cin >> cx[i] >> cy[i];
        flag[i] = 0;
        //输入奶牛坐标，flag记录情况。
    }
    for(int i=1; i<=m; i++)
    {
        cin >> sx >> sy;
        mindis = 1e15;
        dis = 0; //距离清零。
        pos = 0; //pos清零。
        for(int j=1; j<=n; j++)
        {
            if(flag[j] == 1) continue;
            dis = 1ll * (cx[j]-sx) * (cx[j]-sx) + 1ll * (cy[j]-sy) * (cy[j]-sy); //计算距离，也可以写成函数来做。
            if(dis < mindis)
            {
                mindis = dis;
                pos = j;
                //如果距离更小了，更新 mindis 和 pos
            }
        }
        flag[pos] = 1;
    }
    if(n == m)
    {
        cout << 0;
        return 0;
    }
    for(int i=1; i<=n; i++)
    {
        if(flag[i] == 1) continue; //查看情况
        cout << i << endl;
    }
    return 0;
}
```

---

## 作者：rfsfreffr (赞：1)

题意：给你n个点，再给你m个点，对于后面m个点与其最近的一个前n个点，一一配对，最后输出剩下没有配对的前n个点的编号

思路：直接暴力枚举即可

需要注意的是数据较大，需要使用Long Long


# 代码:
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct oi{
	int x,y;
}a[100001],s[100001];
int n,m;
long long dis(oi x,oi y){//计算距离
	return sqrt((long long)((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y)));
}
int pd[10001];
signed main(){
	cin>>n>>m;
	for(int i=1; i<=n; i++){
		scanf("%lld%lld",&a[i].x,&a[i].y);
	}
	for(int i=1; i<=m; i++){
		scanf("%lld%lld",&s[i].x,&s[i].y);
	}
	for(int i=1; i <=m; i++){//枚举配对
		long long minn=1e17;
		int t=0;
		for(int j=1; j<=n; j++){
			if(dis(a[j],s[i])<minn&&pd[j]==0){
				minn=dis(a[j],s[i]);
				t=j;
			}
		}
		pd[t]=1;
	}
	int flag=0;
	for(int i=1; i<=n; i++){//输出答案
		if(pd[i]==0){
			cout<<i<<endl;
			flag=1;
		} 
	}
	if(flag==0){
		cout<<0<<endl;
	}
	return 0;
}
```

---

## 作者：COUPDETAT (赞：1)

## 这题为什么是蓝题啊 发出疑问
### ~~真的是没人做的枚举sb题~~
处理出每头牛和位置之间的距离 让最近的牛坐上去
### 处理坐标：
```cpp
int xy(int x1,int x2,int x3,int x4)
{
	return sqrt(pow(x1-x2,2)+pow(x3-x4,2));
}
```
### 枚举选牛
```cpp
for(int i=1;i<=m;i++)
    {
        int min=20041127123456,t;
        for(int j=1;j<=n;j++)
        {
            if(!match[j])
            {

                int dis=xy(chery[i].x,cow[j].x,chery[i].y,cow[j].y);
                if(dis<min)
                {
                    min=dis;
                    t=j;
                }
            }
        }
        match[t]=1;
	}
```



---

## 作者：封禁用户 (赞：1)

**我们先记录每头奶牛的坐标以及每个位置的坐标，然后，枚举每个位置，去查找满足要求且并未被用过的奶牛，将这头奶牛标上记号，最后，输出没被标上记号的奶牛，但是要注意：所有的奶牛都坐上了座位，则需要输出0，否则会WA一个点。**

```cpp
var n,m,i,j,t,s:longint;
    t1,t2,t3,min:qword;
    x,y,x1,y1:array[1..1000]of int64;//每头奶牛的坐标和每个位置的坐标
    b:array[1..1000]of boolean;//标记奶牛是否坐上位置
begin
  readln(n,m);
  for i:=1 to n do readln(x[i],y[i]);//读入奶牛坐标
  for i:=1 to m do readln(x1[i],y1[i]);//读入位置坐标
  for i:=1 to m do
    begin
      t:=0;min:=400000000000000;//初始化工作
      for j:=1 to n do
        if not b[j] then//当前的奶牛必须要是没用过的
          begin
            t1:=(x[j]-x1[i])*(x[j]-x1[i]);//不能使用sqr，如果用qsr，数据的平方若大于longint的范围，就会出现运行错误
            t2:=(y[j]-y1[i])*(y[j]-y1[i]);
            t3:=t1+t2;//计算距离，不需要用到sqrt，我们只要找到sqrt前的值最小的即可
            if t3<min then
              begin
                t:=j;//保存奶牛编号
                min:=t3;//记录小值
              end;
          end;
      b[t]:=true;//标记上这头奶牛，表示这头奶牛被用过了
          s:=s+1;//奶牛坐到位置上的数量+1
    end;
  if s=n then writeln(0) else//若都坐上了，就输出0，不加上这句，你就与满分拜拜了～
  for i:=1 to n do 
    if not b[i] then writeln(i);//输出没坐上位置的奶牛
end.
```

---

## 作者：wangsiyuanZP (赞：0)

## 分析思路
因为每个座位都有奶牛坐，可每个奶牛不一定有座位。 
于是按座位遍历，对于每个座位，按输入顺序遍历奶牛，如果奶牛没有座位，计算距离，并找到最小值，便利完后找到最小值，并设为有座位。  
设座位在 ${x1,y1}$ 奶牛在 ${x2,y2}$ 。   
距离的计算：$(x1-x2)\times(x1-x2)+(y1-y2)\times(y1-y2)$  
要开 `long long`
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 10005;
int n;

long long sx[N],sy[N],cx[N],cy[N],vis[N];//sx,sy是座位的坐标cx,cy是奶牛的坐标

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i = 0;i<n;i++){
		scanf("%lld%lld",&cx[i],&cy[i]);//注意lld
		vis[i] = 0;
	}
	for (int i = 0;i<m;i++){
		scanf("%lld%lld",&sx[i],&sy[i]);
	}
	int k;
	long long minn;
	for (int i = 0;i<m;i++){
		k = 0,minn = 1e16;
		for (int j = 0;j<n;j++){
			if (!vis[j]){
				long long tmp = (sx[i]-cx[j])*(sx[i]-cx[j])+(sy[i]-cy[j])*(sy[i]-cy[j]);//计算距离
				if (tmp<minn) k = j,minn = tmp;
			}
		}
		vis[k] = 1;
	}
	for (int i = 0;i<n;i++){
		if (!vis[i]) printf("%d\n",i+1);
	}
	if (n == m){
		printf("0\n");//如果没有饥饿的奶牛,则输出0 
	}
	return 0;
}
```

---

## 作者：羚羊WANG (赞：0)

[题目传输门](https://www.luogu.com.cn/problem/P2994)

题目大意：

有$n$头奶牛，$m$个凳子，奶牛抢凳子，求出最后抢不到凳子的奶牛

显然，根据题目数据描述，$n \leq 1000$且$m \leq n$，我们可以考虑暴力

暴力搜索每一个凳子，计算出当前没有凳子的奶牛与当前凳子的距离，取出凳子，标记为可以取到凳子，用$O(nm)$的时间复杂度去计算，最后记得题目说的如果什么都取不到输出$0$

代码:

```cpp
/**
*　　┏┓　　　┏┓+ +
*　┏┛┻━━━┛┻┓ + +
*　 ┃　　　　　　　┃
*　  ┃　　　━　　　┃ ++ + + +
*     ████━████+
*     ◥██◤　◥██◤ +
*　 ┃　　　┻　　　┃
*　┃　　　　　　　┃ + +
*　┗━┓　　　┏━┛
*　　　┃　　　┃ + + + +Code is far away from 　
*　　　┃　　　┃ + bug with the animal protecting
*　　　┃　 　 ┗━━━┓ 神兽保佑,代码无bug　
*　　　┃ 　　　　　　 ┣┓
*　　  ┃ 　　　　　 　┏┛
*　    ┗┓┓┏━┳┓┏┛ + + + +
*　　　　┃┫┫　┃┫┫
*　　　　┗┻┛　┗┻┛+ + + +
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n;
bool vis[1010];
struct node{
	int x,y;
}e1[1010],e2[1010];
double minn;
int minn_id;
int flag=1;
int m;
int Dis(int x1,int yy1,int x2,int yy2){
	return sqrt((x1-x2)*(x1-x2)+(yy1-yy2)*(yy1-yy2));
}
inline void into(){
	n=read();
	m=read();
	for(register int i=1;i<=n;++i)
		{
			e1[i].x=read();
			e1[i].y=read(); 
		}
	for(register int i=1;i<=m;++i)
		{
			e2[i].x=read();
			e2[i].y=read();
		}
	for(register int i=1;i<=m;++i)
		{
			minn=100000000000;
			minn_id=0;
			for(register int j=1;j<=n;++j)
				{
					if(!vis[j])
						{
							int ddis;
							ddis=Dis(e2[i].x,e2[i].y,e1[j].x,e1[j].y);
							if(ddis<minn)
								{
									minn=ddis;
									minn_id=j;
								}
						}
				}
			vis[minn_id]=1;
		}
	for(register int i=1;i<=n;++i)
		if(!vis[i])
			{
				write(i);
				puts("");
				flag=0;
			}
	if(flag)
		write(0);
}
signed main(){
	into();
	return 0;
}

```


---

## 作者：45dino (赞：0)

前言：奶牛都能参加 IOI ，我真是蒻的连奶牛都不如了。

其实模拟即可，枚举桌子，看哪头奶牛最近，因为奶牛的速度都是一样的，所以谁近谁就会抢到桌子。

要注意一些细节：
- 要注意每一张桌子是按时间优先，编号其次的顺序排列的。
- 一头牛不能占两张桌子。
- 记得用 ll ，特判n=m（所有牛都找到了桌子）。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,vis[1001];
pair<int,int> c[1001],p[1001];
int dis(pair<int,int> x,pair<int,int> y)
{
	return (x.first-y.first)*(x.first-y.first)+(x.second-y.second)*(x.second-y.second);
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	if(n==m)
	{
	    cout<<0;
	    return 0;
	}
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&c[i].first,&c[i].second);
	for(int i=1;i<=m;i++)
		scanf("%lld%lld",&p[i].first,&p[i].second);
	for(int i=1;i<=m;i++)
	{
		int ans,minn=1e18;
		for(int l=1;l<=n;l++)
			if(!vis[l])
			{
				int d=dis(c[l],p[i]);
				if(minn>d)
				{
					minn=d;
					ans=l;
				}
			}
		vis[ans]=1;
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])
			cout<<i<<endl;
	return 0;		
}
```


---

