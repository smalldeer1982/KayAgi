# Computer Game

## 题目描述

你正在玩你最喜欢的一款游戏，现在你闯到了最后一关，要和大$Boss$一决高下。

$Boss$有两个属性：生命值$max$和每秒钟回复的生命值$reg$。

你手上有$N$个卷轴，每个卷轴也有两个属性：卷轴使用时$Boss$的最大血量**百分比**$pow_i$（如果$Boss$的血量**百分比**大于$pow_i$，则无法使用这个卷轴）和卷轴每秒钟造成的伤害$dmg_i$。卷轴是一次性的，但是它的效果会持续到游戏结束。

每一秒钟战斗的顺序是：$Boss$先受到所有卷轴造成的伤害，然后回复$reg$点生命值（当然，$Boss$的血量不能超过$max$），然后你使用可以使用的**一个**卷轴。

当某一秒$Boss$受到伤害**并回复血量之后**血量小于等于$0$时，你就赢了。

现在请你回答：你是否能够赢这一局游戏？如果可以，求出最短用时、每一个卷轴是否被使用和使用过的卷轴被使用的时间。

注意：在获胜的那一秒不能使用卷轴

## 样例 #1

### 输入

```
2 10 3
100 3
99 1
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
2 100 10
100 11
90 9
```

### 输出

```
YES
19 2
0 1
10 2
```

# 题解

## 作者：红尘仙 (赞：1)

 [题目传送门](https://www.luogu.com.cn/problem/CF37B)

~~为了赚点贡献分真是辛苦管理大大了。~~

### 解题思路：

  对于一个能自我恢复血量的 BOSS，杀死它唯一的办法就是对他造成的持续的伤害大于它恢复的血量，这个时候才能杀死它，否则永远无法杀死他，那么就可以考虑一下怎么判断是否可以杀死他。
 
  枚举一个卷轴，如果卷轴全部都不能使用，并且现在这个 BOSS 的血量是满血状态，也就是恢复的不比伤害低，然后判断是否都能用就OK了。

杀不死他判断完了，接下来的情况也就是全部按杀死它处置。

### Notice:

做题要模块化。

+ 1 ， 先枚举一遍卷轴，枚举出最大能用的卷轴，这个地方贪心就很简单，因为要杀死他且最短时间内，那么肯定直接拿出最大的伤害打它，总不能拿出最小的伤害去打他。

+ 2 ， 我们判断一下是否有伤害，(没伤害用他干啥）,注意的就是，如果没有伤害也不代表杀不死他，因为时间推移，对他造成的伤害会越来越低或者说，它血量越来越少，那么久可以触发其他的卷轴来打他。

+ 3 ， 判断一下是否可以杀死。
 
### Code

```
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
struct juanzhou
{
	int pow,dem;
}a[maxn];
struct Uesd
{
	int time,number;
}b[maxn];
int n,blood,reb,bound,sum_dem,num=0,Max_num,stand_blood;
bool used[maxn];
bool cmp(Uesd x,Uesd y)
{
	return x.time<y.time;
}
bool flag=0;
void solve()
{
	while(blood>0)//表示BOSS has been alive
	{
		int Max=0;
		for(int i=1;i<=n;i++)
		{
			//只要这个卷轴没被用过，并且可以用，而且取出能攻击的最大伤害
			//每一回合都能对BOSS造成伤害，那肯定是最优的
			if(((blood*100.0/stand_blood)<=a[i].pow) && (!used[i]) && a[i].dem>Max)
			{
				Max=a[i].dem;
				//uesd[i]=true;这个地方注意一下，就是我们还不确定到底需不需要用
				Max_num=i;
			}
		}
			//cout << Max_num<<" Test"<<endl; 
			if(Max!=0)//the demage can demage the BOSS this time
			{
				used[Max_num]=true;//把刚刚的卷轴给他用了
				sum_dem+=Max;//每一秒都需要伤害，那么把总伤害记录一下
				b[++num].number=Max_num;
				b[num].time=bound;//这一回合，也就是这一秒内，使用了该卷轴
			}
			blood-=sum_dem;// 伤害BOSS
			//cout<<sum_dem<<" --------test"<<endl;
			blood+=reb;//耍赖回血
			if(blood>stand_blood)//BOSS的血量不能超过本身的血量
			{
				blood=stand_blood;
			}
			if(blood==stand_blood)//回血之后回到了本来的血量
			{
				int cnt=0;
				for(int kkk=1;kkk<=n;kkk++)
				{
					if( (a[kkk].pow==100) &&(!used[kkk]) )//能用卷轴 
					{
						break;
					}	
					cnt++;
				}
				if(cnt==n)
				{
					flag=1;
					return ;
				}
			}
		bound++;//从 0 回合开始 
	}
}
int main()
{
	n=read(),blood=read(),reb=read();
	for(int i=1;i<=n;i++)
	{
		a[i].pow=read(),a[i].dem=read();
	}
	stand_blood=blood;//因为有个恢复而且不能超过本来的血量，先记录一下本来的血量
	solve();
	if(flag==1)
	{
		cout<<"NO"<<endl;
		return 0;
	}
	cout<<"YES"<<endl;
	cout<<bound<<" "<<num<<endl;
	sort(b+1,b+num+1,cmp);
	for(int i=1;i<=num;i++)
	{
		cout<<b[i].time<<" "<<b[i].number<<endl;
	}
	return 0;
}
```


---

## 作者：ModestCoder_ (赞：1)

模拟题……

每一秒都选符合要求且攻击力最大的卷轴

没有就算了

但是若是BOSS的生命力只增不减且已没有可用的卷轴，输出NO

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 1010
using namespace std;
struct data{
	int p, atk;
}a[maxn];
struct node{
	int sec, id;
}print[maxn];
int n, Max, reg, atk, flag[maxn], cnt, ans;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int main(){
	n = read(), Max = read(), reg = read();
	for (int i = 1; i <= n; ++i) a[i] = (data){read(), read()};
	int sum = Max;
	while (sum > 0){
		sum = min(Max, sum - atk + reg);
		if (sum <= 0) break;
		if (sum >= Max){
			int b = 0;
			for (int i = 1; i <= n; ++i)
				if (a[i].p >= 100 && !flag[i]){
					b = 1; break;
				}
			if (!b) return puts("NO"), 0;
		}
		int Atk = 0, id = 0;
		for (int i = 1; i <= n; ++i)
			if (!flag[i] && 100 * sum <= a[i].p * Max && a[i].atk > Atk) Atk = a[i].atk, id = i;
		if (id) flag[id] = 1, atk += Atk, print[++cnt] = (node){ans, id};
		++ans;
	}
	puts("YES");
	printf("%d %d\n", ans, cnt);
	for (int i = 1; i <= cnt; ++i) printf("%d %d\n", print[i].sec, print[i].id);
	return 0;
}
```


---

## 作者：Ag2WO4 (赞：0)

贪心加模拟的水题。选每回能用的卷轴里伤害最高的，无限模拟直到 boss 死亡或者程序接近超时（死循环）即可。
```python
import time;t=time.time();n,m,r=map(int,input().split());h=m;d=i=0;c=[];n=sorted([list(map(int,input().split()))+[i+1]for i in range(n)],key=lambda i:-i[1])
while 1:
    if i%100==0:
        if time.time()-t>.95:print('NO');break
    h=min(h-d+r,m)
    if h<=0:
        print('YES');print(i,len(c))
        for j in c:print(j[0],j[3])
        break
    for j in n:
        if h*100<=m*j[0]:d+=j[1];c.append([i]+j);n.remove(j);break
    i+=1
```

---

## 作者：Vitamin_B (赞：0)

# 思路
首先先按 $pow$ 从大到小排序，肯定是 $pow$ 越大越**有机会**先使用嘛。

因为数据小，所以接下来只要暴力枚举每个回合即可。如果当前回合中，已经无法再加入卷轴且伤害还不及对方的回血速度，那么你再怎么打它都还是满血，无解了。

否则，就在当前能选的卷轴里面贪心取一个伤害最大的卷轴，这一点可以用优先队列实现，直到它死了就不再继续，输出答案。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
struct node {
	int x, y, id;
	bool operator < (const node& t) const {
		return y < t.y;
	}
} a[1005];
bool cmp (const node& x, const node& y) {
	return x.x > y.x;
}
int n, m, r, sum, j;
vector <pii> ans;
priority_queue <node> q;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m >> r;
	for (int i = 0; i < n; ++ i)
		cin >> a[i].x >> a[i].y, a[i].id = i + 1, a[i].x = m * a[i].x / 100;
	sort (a, a + n, cmp);
	sum = -r;
	for (int i = 0; ; ++ i) {
		m -= max (0, sum);
		if (m <= 0) {
			cout << "YES\n" << i << ' ' << ans.size () << '\n';
			for (pii& k : ans)
				cout << k.first << ' ' << k.second << '\n';
			return 0;
		}
		while (j < n && m <= a[j].x)
			q.push (a[j]), ++ j;
		if (! q.empty ())
			sum += q.top ().y, ans.push_back ({i, q.top ().id}), q.pop ();
		else if (sum <= 0) {
			cout << "NO";
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：ademik (赞：0)

### 分析：

由于 Boss 的血量 $\le 1000$，那么我们可以在 $2000$ 以内的时间完成游戏（如果可能的话），可以直接枚举时间。

我们假设 Boss 的血量恢复为 $delta$，那么每个卷轴的作用即将 $delta$ 减去一个值。注意到 $delta$ 的值是不断减小的，也就是说，Boss 的血量要么为 $100\%$，要么小于上一个时刻的血量，即 Boss 的血量单调递减。

由于可以使用卷轴的约束是要求血量小于一个值，所以当某个时刻 Boss 的血量降低到给定值后，在这个时刻之后我们一直可以选择使用该卷轴。故而我们只需要在每一个时刻贪心的选择伤害值最大的卷轴即可。

对于无解的判断即为当前无可用卷轴、当前 $delta > 0$ 和 当前血量大于等于上一次的血量。

### Code：

```cpp
# include <bits/stdc++.h>
# define TIME 1e3 * clock() / CLOCKS_PER_SEC
using namespace std;
typedef long long i64;
typedef pair < int, int > pii; 
const int N = 1e5 + 50;
int n, maxn, delta, mark[N]; 
struct node {
	int x, y, id; 
	bool operator <(const node &tmp) const {
		return x > tmp.x; 
	}
} date[N];  
int main()
{
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >>n >>maxn >>delta; 
    for(int i = 1; i <= n; i ++) cin >>date[i].x >>date[i].y, date[i].id = i; 
    sort(date + 1, date + 1 + n); 
    priority_queue < pii > q; 
    int now = maxn, pos = 1, t = -1, pre = -1;
	vector < int > ans;  
    while(true) {
    	t ++; 
		if(delta > 0) now = min(maxn, now + delta); 
        else {
            now += delta; 
            if(now <= 0) break; 
        }
        while(pos <= n && date[pos].x * maxn >= now * 100) {
            q.push(make_pair(date[pos].y, date[pos].id)); 
            pos ++; 
        }
        if(!q.empty()) {
        	delta -= q.top().first;
			mark[q.top().second] = t; 
			ans.push_back(q.top().second); 
			q.pop(); 
        }
        if(pre != -1 && now >= pre && q.empty() && delta >= 0) {
            cout <<"NO" <<endl;
            return 0; 
        }
        pre = now; 
    }
    cout <<"YES" <<endl; 
    cout <<t <<" " <<ans.size() <<endl;
    for(auto x : ans) {
    	cout <<mark[x] <<" " <<x <<endl; 
	}
    return 0;  
}

```

---

## 作者：XL4453 (赞：0)

### 题目分析

本题可以考虑贪心。

首先是无解情况的判断，可以发现，如果将所有的满血就能使用的卷轴都使用了也不能使得总伤害值大于恢复值，那么一定无解，否则一定有解，这是显然的。

对于一个当前血量，肯定是选择能使用的卷轴中能造成伤害更高的那一个使用。

这样的一个贪心的正确性是可以保证的。

这是由于 BOSS 生命值有上限且一直回固定量的血，说明如果生命值小于了生命上限就一定有当前卷轴每秒造成伤害大于回血量，也就不存在为了考虑 BOSS 以后会回血导致某一些卷轴不能用的情况。

换句话说，一旦某一个卷轴在某一个时刻能用了，那么从这个时刻以后的所有时刻这个卷轴都一定能用。

而且使用过卷轴后伤害会一直持续，所以得出一定要优先使用能使用的卷轴中能造成伤害更高的一个。

--------
那么就考虑先将所有的元素按照使用血量从大到小排序，用一个指针记录当前血量能使用的卷轴。

然后用一个大根堆记录一下当前能使用的卷轴，每一次取出堆顶元素，计算伤害，拓展指针即可。

当然这题的数据范围很小，不用堆直接枚举也能过 ~~（不愧是水蓝水蓝的题）~~。

------------
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
	int num,pow,atk;
}p[1005];
int maxhp,reg,n,hp,sum,tim,book[1005],maxn,maxi,ans[1005],ans2[1005],tot;
int main(){
	scanf("%d%d%d",&n,&maxhp,&reg);
	hp=maxhp;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&p[i].pow,&p[i].atk);
		if(p[i].pow==100)sum+=p[i].atk;
	}
	if(sum<=reg){
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	sum=0;
	while(hp>0){
		hp=hp-sum+reg;
		hp=min(hp,maxhp);
		if(hp<=0)break;
		maxn=0;maxi=-1;
		for(int i=1;i<=n;i++){
			if(!book[i]&&hp*100<=p[i].pow*maxhp&&p[i].atk>maxn){
				maxn=p[i].atk;
				maxi=i;
			}
		}
		if(~maxi){
			book[maxi]=1;
			ans[++tot]=tim;
			ans2[tot]=maxi;
			sum+=maxn;
		}
		tim++;
	}
	printf("%d %d\n",tim,tot);
	for(int i=1;i<=tot;i++)
	printf("%d %d\n",ans[i],ans2[i]);
	return 0;
}
```


---

## 作者：xh39 (赞：0)

# 简单的模拟
#### 找到一个可用并且没用过中攻击力最大的。然后每用一个卷轴都把它的时间和序号记录在一个二维数组里,并把攻击变量+=dmg,用的卷轴数目++。
#### 判断是不是打不赢很简单,就是血量越来越多(**当然得用完所有的卷轴还越来越多才可以判断**)

# 代码仅供参考,请勿抄袭~~(小心被洛谷......)~~!!!
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
double a[1005],b[1005],used[1005][2];
bool mark[1005]={0};
int main(){
    int n,maxa,xue,reg,gong=0,Max,maxnum,seconds=0,sum=0,i,j;
    cin>>n>>maxa>>reg;
    if(maxa==0){
        cout<<0<<endl;
    }
    xue=maxa;
    for(i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    while(xue>0){
        Max=0;
        for(i=1;i<=n;i++){
            if(((xue*100.0/maxa)<=a[i])&&(!mark[i])&&(b[i]>Max)){
                Max=b[i];
                maxnum=i;
            }
        }
        if(Max!=0){
            mark[maxnum]=1;
            gong+=Max;
            used[++sum][0]=seconds;
            used[sum][1]=maxnum;
        }
        xue-=gong;
        xue=min(xue+reg,maxa);
        if(xue>=maxa){
            for(j=1;j<=n;j++){
                if((a[j]==100)&&(!mark[j])){
                    break;
                }
                if(j==n){
                    cout<<"NO";
                    return 0;
                }
            }
        }
        seconds++;
    }
    cout<<"YES"<<endl;
    cout<<seconds<<" "<<sum<<endl;
    for(i=1;i<=sum;i++){
        cout<<used[i][0]<<" "<<used[i][1]<<endl;
    }
    return 0;
}

```

---

