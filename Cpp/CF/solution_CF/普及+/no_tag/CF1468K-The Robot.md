# The Robot

## 题目描述

在一个无尽的原野上有一个机器人，开始时它位于 $(0,0)$，它将执行一个由 L,R,D,U 四种命令组成的序列，当一个命令被执行时，机器人会向这个命令指定的方向移动一格：


* L : 向左移动一格。（$x$ 减一）
* R : 向右移动一格。（$x$ 加一）
* D : 向下移动一格。（$y$ 减一）
* U : 向上移动一格。（$y$ 加一）


你的任务是在一个格子中放置一个障碍物，使机器人在执行完命令后恰好在 $(0,0)$。当然，你不能将障碍物放在 $(0,0)$ 上。

注：数据保证若你不放置障碍物，机器人执行完命令后将不会停在 $(0,0)$。

若机器人移动后的格子有障碍物，障碍物会阻止机器人行动，机器人会留在原地同时障碍物也不会消失。

## 样例 #1

### 输入

```
4
L
RUUDL
LLUU
DDDUUUUU```

### 输出

```
-1 0
1 2
0 0
0 1```

# 题解

## 作者：__PJL__ (赞：3)

观察题目，可以发现如果把障碍放在机器人没有经过的地方是无意义的，所以只能把障碍放在机器人一定会走到的地方上，暴力枚举障碍的位置即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 1;

int t, x, y, a[MAXN];
vector<pair<int, int>> c;
map<char, pair<int, int>> mp;
string s;

int main() {
    mp['L'] = {-1, 0}, mp['R'] = {1, 0};
    mp['D'] = {0, -1}, mp['U'] = {0, 1};
    cin >> t;
    while(t--) {
        bool q = false;
        cin >> s;
        int x = 0, y = 0;
        for(int i = 0; i < s.size(); i++) {
            x += mp[s[i]].first, y += mp[s[i]].second;
            if(x != 0 || y != 0) {
                c.push_back({x, y});
            }
        }
        for(int i = 0; i < c.size(); i++) {
            x = 0, y = 0;
            for(int j = 0; j < s.size(); j++) {
                int newx = x + mp[s[j]].first, newy = y + mp[s[j]].second;
                if(c[i].first != newx || c[i].second != newy) {
                    x = newx, y = newy;
                }
            }
            if(x == 0 && y == 0) {
                cout << c[i].first << " " << c[i].second << "\n";
                q = true;
                break;
            }
        }
        if(!q) {
            cout << "0 0\n";
        }
    }
    return 0;
}
```

---

## 作者：VitrelosTia (赞：2)

首先题里有一些事情需要确认：障碍物不会消失、机器人原路径一定回不到终点。

一个显然的事情是你这个障碍物必须放在机器人经过的路上，不然对于机器人没有任何影响。然后你发现 $n \le 5000$，$O(n^2)$ 乱搞都行，于是对于每个经过的位置都试放障碍物判断就行了。

```
typedef pair <int, int> pii;
#define x first
#define y second

string s; int n;
bool operator == (pii a, pii b) { return a.x == b.x && a.y == b.y; }
bool check(int qx, int qy) {
	pii pos, qwq = {qx, qy};
	for (int i = 1; i <= n; i++) {
		if (s[i] == 'L') {
			pos.x--;
			if (pos == qwq) pos.x++;
		}
		if (s[i] == 'R') {
			pos.x++;
			if (pos == qwq) pos.x--;
		}
		if (s[i] == 'D') {
			pos.y--;
			if (pos == qwq) pos.y++;
		}
		if (s[i] == 'U') {
			pos.y++;
			if (pos == qwq) pos.y--;
		}
	}
	return pos == make_pair(0, 0);
}
void solve() {
	cin >> s; n = s.size(); s = " " + s;
	pii now = {0, 0};
	for (int i = 1; i <= n; i++) {
		if (s[i] == 'L') now.x--;
		if (s[i] == 'R') now.x++;
		if (s[i] == 'D') now.y--;
		if (s[i] == 'U') now.y++;
		if (check(now.x, now.y)) {
			cout << now.x << ' ' << now.y << '\n';
			return;
		}
	}
	cout << "0 0\n";
}
```

---

## 作者：hzoi_liuchang (赞：2)

## 分析
因为只能放一个障碍，所以我们一定要把障碍放在机器人的必经之路上

我们只需要枚举机器人会经过哪些点

然后分别在这些点放上障碍判断是否合法即可

时间复杂度 $O(n^2)$
## 代码
``` cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define rg register
inline int read(){
	rg int x=0,fh=1;
	rg char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*fh;
}
const int maxn=5e3+5;
int t,len,tp,x[maxn],y[maxn];
char s[maxn];
bool jud=0;
void dfs(rg int nx,rg int ny,rg int dep){
	x[++tp]=nx;
	y[tp]=ny;
	if(dep>len) return;
	if(s[dep]=='L') dfs(nx-1,ny,dep+1);
	else if(s[dep]=='R') dfs(nx+1,ny,dep+1);
	else if(s[dep]=='D') dfs(nx,ny-1,dep+1);
	else dfs(nx,ny+1,dep+1);
}
int main(){
	t=read();
	while(t--){
		scanf("%s",s+1);
		len=strlen(s+1);
		jud=0;
		tp=0;
		dfs(0,0,1);
		rg int qdx,qdy,zdx,zdy;
		for(rg int i=1;i<=tp;i++){
			qdx=qdy=0;
			for(rg int j=1;j<=len;j++){
				if(s[j]=='L') zdx=qdx-1,zdy=qdy;
				else if(s[j]=='R') zdx=qdx+1,zdy=qdy;
				else if(s[j]=='D') zdx=qdx,zdy=qdy-1;
				else zdx=qdx,zdy=qdy+1;
				if(zdx==x[i] && zdy==y[i]) continue;
				else qdx=zdx,qdy=zdy;
			}
			if(qdx==0 && qdy==0){
				jud=1;
				printf("%d %d\n",x[i],y[i]);
				break;
			}
		}
		if(!jud) printf("0 0\n");
	}
	return 0;	
}
```

---

## 作者：abs20187 (赞：1)

由于只放一个障碍，把障碍放在机器人**未放障碍**时经过的路线外是毫无意义的，因为机器人根本不会遇到这个障碍。

因此，我们仅需枚举所有机器人**未放障碍**时经过的格子，都尝试在这些格子放上障碍，看机器人会不会回到 $(0,0)$。值得注意的是，放障碍时枚举的格子中如有 $(0,0)$，要直接跳过。

代码实现起来较简单，用一个数组记录所有机器人未放障碍时经过的格子，for 循环枚举即可，复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int> >a;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		int x=0,y=0;
		a.clear();
		for(int i=0;i<s.size();i++)
		{
			if(s[i]=='L')
			{
				x--;
			}
			if(s[i]=='R')
			{
				x++;
			}
			if(s[i]=='U')
			{
				y++;
			}
			if(s[i]=='D')
			{
				y--;
			}
			a.push_back({x,y});
		}
		int ansx=0,ansy=0;
		for(auto i:a)
		{
			if(i.first==i.second&&i.first==0)
			{
				continue;
			}
			int tmpx=0,tmpy=0;
			for(int j=0;j<s.size();j++)
			{
				if(s[j]=='L')
				{
					if(tmpx-1==i.first&&tmpy==i.second)
					{
						continue;
					}
					tmpx--;
				}
				if(s[j]=='R')
				{
					if(tmpx+1==i.first&&tmpy==i.second)
					{
						continue;
					}
					tmpx++;
				}
				if(s[j]=='U')
				{
					if(tmpx==i.first&&tmpy+1==i.second)
					{
						continue;
					}
					tmpy++;
				}
				if(s[j]=='D')
				{
					if(tmpx==i.first&&tmpy-1==i.second)
					{
						continue;
					}
					tmpy--;
				}
			}
			if(tmpx==tmpy&&tmpy==0)
			{
				ansx=i.first,ansy=i.second;
				break;
			}
		}
		cout<<ansx<<" "<<ansy<<"\n";
	}
    return 0;
}
```
最后提醒大家：

**多测不清空，暴零两行泪。**

---

## 作者：conti123 (赞：1)

## CF1468K The Robot

关于我 VP 时想了半天的线性做法没想出来，一看数据范围 $O(n^2)$ 随便过？

发现数据范围很小，可以暴力模拟障碍物放在哪里，然后模拟一遍看能否回到原点。

由于障碍物一定至少阻挡了机器人一次才会放，所以我们处理一下机器人如果走了这一步会到哪里，然后在那里放一个障碍物即可。

```cpp
void solve(){
	string s;
	int x=0,y=0;
	cin>>s;
	int st=0;
	for(int i=0;i<s.size();i++){
		if(s[i]=='L')
			x--;
		if(s[i]=='R')
			x++;
		if(s[i]=='D')
			y--;
		if(s[i]=='U')
			y++;
		if(x==0&&y==0){
			st=i+1;
		}
	}
	if(st==s.size()){
		cout<<"1919810 1919810\n";
		return ;
	}
	vector<pair<int,int> >B;
	int nx=0,ny=0;
	x=0,y=0;
	for(int i=0;i<s.size();i++){
		nx=x,ny=y;
		if(s[i]=='L')
			nx--;
		if(s[i]=='R')
			nx++;
		if(s[i]=='D')
			ny--;
		if(s[i]=='U')
			ny++;
		B.push_back({nx,ny});//预判机器人路线放障碍物
		x=nx,y=ny;
	}
	for(auto [sx,sy]:B){//暴力枚举障碍物放哪里
		x=0,y=0;
	//	cout<<sx<<" "<<sy<<"\n";
		for(int i=0;i<s.size();i++){
			nx=x,ny=y;
			if(s[i]=='L')
				nx--;
			if(s[i]=='R')
				nx++;
			if(s[i]=='D')
				ny--;
			if(s[i]=='U')
				ny++;
			if(nx==sx&&ny==sy)
				continue;
			x=nx,y=ny;
		}
		if(x==0&&y==0){
			cout<<sx<<" "<<sy<<"\n";
			return ;
		}
	}
	cout<<"0 0\n";
}
```

---

## 作者：renzecheng (赞：0)

# CF1468K The Robot
## 题目描述
  找到一种方式，在一个位置上放置障碍物，使机器人回到起点。
## 分析
> 若机器人移动后的格子有障碍物，障碍物会阻止机器人行动，机器人会留在原地同时障碍物也不会消失。

如果要改变机器人的终点位置，就需要放置障碍物使其改变移动，也就是说，障碍物必须就要放在机器人的路线上。  
观察数据范围可知：
  $$
\sum_{i = 1}^{t} s_i 	 \le 5000
$$  
所以可以暴力枚举路线，模拟在路线上除 $$(0,0)$$ 外每一点上放障碍物后是否能回到 $$(0,0)$$。复杂度 $$ O(n^2)$$。
## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
string s; 
int n;
bool check(int x,int y)
{
	int tpx=0,tpy=0;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='L'&&(tpx-1!=x||tpy!=y))tpx--;
		if(s[i]=='R'&&(tpx+1!=x||tpy!=y))tpx++;
		if(s[i]=='D'&&(tpx!=x||tpy-1!=y))tpy--;
		if(s[i]=='U'&&(tpx!=x||tpy+1!=y))tpy++;
	}
	if(tpx==0&&tpy==0) return 1;
	else return 0;
}
void solve()
{
	cin>>s;
	n=s.size();
	int tpx=0,tpy=0;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='L')tpx--;
		if(s[i]=='R')tpx++;
		if(s[i]=='D')tpy--;
		if(s[i]=='U')tpy++;
		if(check(tpx,tpy)==1&&(tpx!=0||tpy!=0))
		{
			cout<<tpx<<' '<<tpy<<"\n";
			return;
		}
	}
	cout<<"0 0\n";
}
int main()
{
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}

```
### 评测结果
![](https://cdn.luogu.com.cn/upload/image_hosting/7yzauf5i.png)

---

## 作者：ATION001 (赞：0)

最多 $5000$ 次操作，因此可以暴力。

注意到放在没有经过的点上没有意义（机器人根本不会到那里去）。

因此我们枚举每一个机器人经过的点，随后跳过当前操作向后暴力模拟，判断是否会回到 $(0,0)$ 即可。
## 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int t,a[200][2];
int main(){
	a['L'][0]=-1,a['R'][0]=1,a['D'][1]=-1,a['U'][1]=1;
	for(cin>>t;t;t--){
		cin>>s;
		bool flag=true;
		int dx=0,dy=0;
		for(int i=0;i<s.size()&&flag;i++){
			dx=dx+a[s[i]][0],dy=dy+a[s[i]][1];
			int x=0,y=0;
			for(int j=0;j<s.size();j++){
				if(x+a[s[j]][0]==dx&&y+a[s[j]][1]==dy){
					continue;
				}else{
					x+=a[s[j]][0],y+=a[s[j]][1];
				}
			}
			if((!x)&&(!y)){
				cout<<dx<<" "<<dy<<'\n',flag=false;
			}
		}
		if(flag){
			cout<<"0 0"<<'\n';
		}
	}
}
```

---

## 作者：_d_h_f (赞：0)

## Solution

这道题数据范围比较小，$s$ 的长度只有 $5000$，暴力的时间复杂度为 $O(n^2)$，在这个数据下完全可以过。

不难看出，如果障碍放在机器人没有经过的地方，那么机器人的路径不会改变，终点也就不会是原点了。所以我们只需要枚举机器人所经过的点坐标当成障碍所在的地方，再沿着原来的指令跑一遍就可以了。

## Code


```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

typedef pair<int, int> PII;

vector<PII> v;

int tt;

char s[5005];

PII a, ans;

PII query(int x, int y, int i) { // 根据指令算出下一个点的坐标 
	
	if (s[i] == 'L')
		x--;
			
	if (s[i] == 'R')
		x ++;
				
	if (s[i] == 'U')
		y ++;
				
	if (s[i] == 'D')
		y --;
		
	return make_pair(x, y);
	
}

signed main() {

	scanf("%lld", &tt);
	
	while (tt--) {
		
		scanf("%s", s + 1);
		
		int n = strlen(s + 1);
		
		// 不要忘记初始化 
		
		a.first = a.second = ans.first = ans.second = 0;
		
		v.clear();
		
		for (int i = 1; i <= n; ++i) {
			
			a = query(a.first, a.second, i);
				
			v.push_back(a);
			
		}
		
		for (int j = 0; j < v.size(); ++j) {
			
			PII p = v[j];
			
			if (p.first == 0 && p.second == 0)
				continue;
			
			a.first = a.second = 0;
			
			for (int i = 1; i <= n; ++i) {
				
				PII b = query(a.first, a.second, i);
			
				if (b.first == p.first && b.second == p.second)
					continue;
				
				a = b;
				
			}
			
			if (a.first == 0 && a.second == 0)
				ans = p;
			
		}
		
		printf("%lld %lld\n", ans.first, ans.second);
		
	}

	return 0;

}

```

---

