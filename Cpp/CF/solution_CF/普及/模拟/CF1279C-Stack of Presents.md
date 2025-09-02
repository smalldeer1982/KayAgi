# Stack of Presents

## 题目描述

Santa has to send presents to the kids. He has a large stack of $ n $ presents, numbered from $ 1 $ to $ n $ ; the topmost present has number $ a_1 $ , the next present is $ a_2 $ , and so on; the bottom present has number $ a_n $ . All numbers are distinct.

Santa has a list of $ m $ distinct presents he has to send: $ b_1 $ , $ b_2 $ , ..., $ b_m $ . He will send them in the order they appear in the list.

To send a present, Santa has to find it in the stack by removing all presents above it, taking this present and returning all removed presents on top of the stack. So, if there are $ k $ presents above the present Santa wants to send, it takes him $ 2k + 1 $ seconds to do it. Fortunately, Santa can speed the whole process up — when he returns the presents to the stack, he may reorder them as he wishes (only those which were above the present he wanted to take; the presents below cannot be affected in any way).

What is the minimum time required to send all of the presents, provided that Santa knows the whole list of presents he has to send and reorders the presents optimally? Santa cannot change the order of presents or interact with the stack of presents in any other way.

Your program has to answer $ t $ different test cases.

## 样例 #1

### 输入

```
2
3 3
3 1 2
3 2 1
7 2
2 1 7 3 4 5 6
3 1
```

### 输出

```
5
8
```

# 题解

## 作者：Goodrage (赞：5)

归纳+模拟

#### 思路分析

礼物 $i$ 的初始位置为 $pos_i$ （从栈顶数第 $pos_i$ 个） 。送出的第 $i$ 个礼物为 $b_i$ ， 所以要送出的礼物的初始位置为 $pos_{b_i}$ 。

记拿到礼物的最低深度为 $\textit{curpos}$  。因为题面中操作是只拿到需要的礼物， 其他的放回，所以位置在 $\textit{curpos}$ 下面的礼物不会被改变位置。

假如我们需要寻找并拿出的礼物 $b_i$ 在 $\textit{curpos}$ 之下 （ **包括等于** ，过会说 ）， 那么必须把前面的全拿出来，拿出需要的， 再都放回去。此时已经送出了 $i$ 个礼物，因为都在 $b_i$ 上面， 所以 $b_i$ 现在的位置为 $pos_{b_i} - i$ ， 只要套公式 $2k - 1$ 就可以。

但是如果礼物位于 $\textit{curpos}$ 之上，那么存在方法将它排在最上面。前面取出位于 $\textit{curpos}$ 的礼物后可以将上面的礼物排序，使得这一次拿到的礼物 （如果在上面）恰好在最顶上 。至于如何排序 ... 我们聪明的圣诞老人一定会知道，这里不多赘述 。

**关于取等** 。在洛谷和 CF 上 ，取等和不取等都可以 AC 。但是因为被线下的毒瘤数据 hack 了，所以还是取等了。但是每个 $pos_{ b_i }$ 应是不一样的 ，毕竟两个礼物原来不能一起位于同一位置 ……

哦对了 ,

开 ```long long``` ！否则会 [蛙](https://www.luogu.com.cn/record/66830345)

#### 代码解析

```cpp
//spin it back now
#include<bits/stdc++.h>
using namespace std;
#define int long long //开 long long
const int sze=1e5+10;
int a[sze],b[sze],pos[sze];//原始顺序，拿出顺序，原始位置
signed main()
{
	int t;
	scanf("%lld",&t);
	for(int asdf=1;asdf<=t;asdf++)//选用数据组数变量，避免重名
	{
		int n,m;
		scanf("%lld%lld",&n,&m);
		int curpos=0;//最低位置，要清零
		int ans=0;//需要步数，要清零
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			pos[a[i]]=i;//原始位置
		}
		for(int i=1;i<=m;i++)
		{
			scanf("%lld",&b[i]);//现在送出礼物 b[i]
			if(curpos<=pos[b[i]])//之前没动过，需要下去找
			{
				ans+=(2*((pos[b[i]]-i))+1);//找，添加步数
				curpos=pos[b[i]];//摸的更低了，更新最低位置
			}
			else
				ans++;//已经动过了，在栈顶直接拿出就行
		}
		printf("%lld\n",ans);//输出多组，要回车
		
	}
	return 0;
}

```
#### 评测结果

[有等号](https://www.luogu.com.cn/record/66830428)

[没等号](https://www.luogu.com.cn/record/66822441)

鸣谢：[洛浔](https://www.luogu.com.cn/user/151947) （帮助调试发现取等问题）

---

## 作者：zhangqiuyanAFOon2024 (赞：1)

### 思路
我们先读题，Santa 有一个送礼物的清单，他必须按照清单上面的顺序送礼物，问时间。

而拿了一件礼物之后可以改变上面的顺序，所以取上面的只需 $2\times0+1=1$ 的时间。

怎么做呢，我们可以打一个标记，是第一个的位置，如果位置比标记高，只需 $1$ 的时间；如果位置比标记低，则需要 $2\times k+1=1$ 的时间，然后改变标记。

最后输出答案。

### 代码
```cpp
#include<水题>
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10;
int a[maxn],b[maxn];//
void solve(){
	int n,m,x;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>x;
		b[x]=i;
	}//位置
	cin>>x;
	m--;
	int time=0,maxx=x;//maxx为标记
	time=(2*(b[x]-1)+1);//第一个的时间
	int k=1;
	while(m--){
		cin>>x;
		if(b[x]<b[maxx]) time++;//直接拿
		else time+=2*(b[x]-1-k)+1,maxx=x;//耗时间
		k++;
	}
	cout<<time<<endl;
}
signed main(){
	int T;
	cin>>T;//多组
	while(T--) solve();
	return 0;
}
```

---

## 作者：dd_d (赞：1)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/15211352.html)
### Sol  
考虑每次读进一个 $b_i$，就从 $a$ 数组中统计出答案。  
每次对于一个 $b_i$，可以将 $a$ 数组中对应位置的前缀丢到一个 $vis$ 里。  
若后面读进的 $b_i$ 的 $vis$ 值为 $1$，那么他对于答案没有贡献。  
因为题目中保证了各个数不唯一，所以这个做法一定是正确的。  
### Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
#define int long long
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=2e5+1;
int n,m,tot,ans,s[N],a[N],top,T,vis[N];
signed main()
{
	T=read();
	while (T--)
	{
		n=read(); m=read();	top=n;
		for (int i=1;i<=n;i++)
			s[top--]=read();
		tot=0; ans=0; top=n;
		memset(vis,0,sizeof(vis));
		for (int i=1;i<=m;i++)
		{
			int x=read();
			if (vis[x])
			{
				ans++; vis[x]=0; tot--;
			}
			else
			{
				do
				{
					vis[s[top]]=1;
					tot++;
				}while (s[top--]!=x);
				ans+=tot*2-1; tot--; 
			}
		}
		writeln(ans);
	}
}




```

---

## 作者：czh___ (赞：0)

### 思路：

我们每拿出一个新的礼物，就要判断一下在这个范围内能不能拿出更多的礼物，因为在这种情况下拿出礼物的是时间是 $1$。二分找到这个礼物的位置，然后再计算就好了。注意要开 long long。
代码如下：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxx=1e5+100;
struct node{
	int pos;
	int num;
	bool operator <(const node &a)const{
		return num<a.num;
	}
}p[maxx];
int a[maxx],b[maxx];
int n,m;

int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) scanf("%d",&p[i].num),p[i].pos=i;
		for(int i=1;i<=m;i++) scanf("%d",&a[i]);
		sort(p+1,p+1+n);
		ll ans=0;
		int j;
		for(int i=1;i<=n;i++) b[i]=p[i].num;
		for(int i=1;i<=m;)
		{
			int pos=lower_bound(b+1,b+1+n,a[i])-b;
			pos=p[pos].pos;
			ans+=(2ll*((ll)pos-i)+1ll);
			for(j=i+1;j<=m;j++)
			{
				int pos1=lower_bound(b+1,b+1+n,a[j])-b;
				pos1=p[pos1].pos;
				if(pos1<pos) ans+=1ll;
				else break;
			}
			i=j;
		}
		cout<<ans<<endl;
	}
	return 0;
}

```

[改编于](https://blog.csdn.net/starlet_kiss/article/details/104163060?ops_request_misc=&request_id=&biz_id=102&utm_term=Stack%20of%20Presents&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-2-104163060.142^v100^pc_search_result_base5&spm=1018.2226.3001.4187)

---

