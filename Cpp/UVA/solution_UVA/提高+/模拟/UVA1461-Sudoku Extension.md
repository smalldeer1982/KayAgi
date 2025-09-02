# Sudoku Extension

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4207

[PDF](https://uva.onlinejudge.org/external/14/p1461.pdf)

# 题解

## 作者：zhczcg314 (赞：1)


### 这是本人的第一篇题解。

这道题是数独的进阶版本，基础数独可以去看 [P1784 数独](https://www.luogu.com.cn/problem/P1784)。

~~由于本人比较菜,~~ 我来给出一篇搜索的题解。

题目大致意思是说：给出 $N$ 组数据，每组数据给出一个没有填充的数独，其中 `0` 代表没有填充的空位, 1$\sim$9 这些数字表示这个位置已经被填上了数字。另外，本题特殊的地方在于如果输入中有 `e`，则这个位置需要用偶数填充；如果这个位置是 `o`，则需要用奇数填充。如果这个位置是用其他字母代替，则所有用这个字母代替的位置都需要用一种数字填充。要求输出这个数独可行性解的数量。

用搜索去解决数独，无非就是两点：1. 状态压缩 2. 剪枝

- 数独问题需要很多的位运算和状态压缩技巧，在这里不详细赘述。
  
- 至于剪枝，这道题范围很小，所以说一个搜索顺序的优化就可以了。
  

给出这道题的代码：

```cpp
#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> tags[200];
char sudoku[9][9];
int row[9], col[9], block[3][3], ones[1 << 9], chr[150];
int N, cnt, ans;
void dfs(int cnt);
void stepping(int x, int y, int num, int cnt, int flag){
    //备份
    char backup = sudoku[x][y];
    if(flag){
        chr[sudoku[x][y]] = num;
    }
    sudoku[x][y] = num + '0';
    row[x] ^= (1 << (num - 1));
    col[y] ^= (1 << (num - 1));
    block[x / 3][y / 3] ^= (1 << (num - 1));
    
    dfs(cnt - 1);
    
    sudoku[x][y] = backup;
    if(flag){
        chr[sudoku[x][y]] = 0;
    }
    row[x] ^= (1 << (num - 1));
    col[y] ^= (1 << (num - 1));
    block[x / 3][y / 3] ^= (1 << (num - 1));
}
void dfs(int cnt){
    //填完数字，出口
    if(cnt == 0){
        //判断情况合法性
        for(int i = 'a'; i <= 'z'; i ++){
            if(i == 'e' || i == 'o' || !tags[i].size())  continue;
            auto tmp = sudoku[tags[i][0].first][tags[i][0].second];
            for(auto j : tags[i]){
                if (sudoku[j.first][j.second] != tmp){
                    //不合法，直接return
                    return;
                }
            }
        }
        //找到一个解决方案，ans++
        ans ++;
        return;
    }
    //优化搜索顺序
    int x = 0, y = 0, _min = 100, min_state = 0;
    for(int i = 0; i < 9; i ++){
        for(int j = 0; j < 9; j ++){
            //已经填过数字，continue
            if(sudoku[i][j] >= '1' && sudoku[i][j] <= '9'){
                continue;
            }
            int now_state = row[i] & col[j] & block[i / 3][j / 3];
            if(ones[now_state] < _min){
                _min = ones[now_state];
                min_state = now_state;
                x = i;
                y = j;
            }
        }
    }
    for(int i = 0; i < 9; i ++){
        chr[sudoku[x][y]] = i;
        while(min_state){
            int lowbit = min_state & -min_state;
            int num = int(log2(lowbit)) + 1;
            if(sudoku[x][y] == '0'){
                stepping(x, y, num, cnt, false);
            }
            if(sudoku[x][y] >= 'a' && sudoku[x][y] <= 'z' && sudoku[x][y] != 'e' && sudoku[x][y] != 'o'){
                if(chr[sudoku[x][y]] == 0){
                    stepping(x, y, num, cnt, true);
                }
                else if(num == chr[sudoku[x][y]]){
                    stepping(x, y, num, cnt, false);
                }
            }
            if((sudoku[x][y] == 'e' && !(num % 2)) || (sudoku[x][y] == 'o' && (num % 2))){
                stepping(x, y, num, cnt, false);
            }
            min_state -= lowbit;
        }
    }
    return;
}

int main(){
    for(int i = 0; i <= (1 << 9) - 1; i ++){
        int tmp = i;
        while(tmp){
            ones[i] ++;
            tmp -= tmp & -tmp;
        }
    }
    cin >> N;
    while(N --){
        fill(row, row + 9, (1 << 9) - 1);
        fill(col, col + 9, (1 << 9) - 1);
        fill(block[0], block[0] + 9, (1 << 9) - 1);
        cnt = 0;
        ans = 0;
        for(int i = 0; i < 9; i ++){
            for(int j = 0; j < 9; j ++){
                cin >> sudoku[i][j];
                //标记该字符所有位置
                tags[sudoku[i][j]].push_back({i, j});
                //已填数字
                if(sudoku[i][j] >= '1' && sudoku[i][j] <= '9'){
                    row[i] ^= 1 << (sudoku[i][j] - '0' - 1);
                    col[j] ^= 1 << (sudoku[i][j] - '0' - 1);
                    block[i / 3][j / 3] ^= 1 << (sudoku[i][j] - '0' - 1);
                }
                //未填数字
                else{
                    cnt ++;
                }
            }
        }
        dfs(cnt);
        cout << ans << endl;
    }
}
```
欢迎指出错误

---

## 作者：FanYongchen (赞：1)

看到数独，第一秒想到的就是暴力。

这道题暴力是可以过的。

题目为：输入一个由字母与数字的$9*9$的数独，各字符含义如题目描述，要求的是方案总个数。

首先，不了解数独的可以看一下：[数独](https://baike.baidu.com/item/%E6%95%B0%E7%8B%AC/74847?fr=aladdin)

然后，读题：

- 数组可能先给出了一个数字

- $o$只能填奇数

- $e$只能填偶数

- 其他**相同字母**处必须填**同一个数**

所以，$o,e$两个字母特判一下，其他字母填的数保存起来。

当然，还需要几个剪枝：

1. 每次选取可填的数最少的一个点。

2. 若有一个点只能填一个数或这个点是一个字母，并且填了这个数后不论搜索成功或失败，都要直接结束本次搜索。

更多注释看代码：

```cpp
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
const int N=9;//地图大小 
int row[11],col[11],matrix[11];
//用几个二进制数表示这一行、列、九宫格有没有填过，就是卡常 
int ch[201]={0};//每个字母所对应的数字 
char mp[11][11];//数独 
int vis[11][11];//记录每个点填的数，可以判断这个点有没有填过 
int ans=0;//方案个数 
void Put(int i,int j,int k)//将k填入第i行第j列 
{
    row[i]|=(1<<k),col[j]|=(1<<k),matrix[(i-1)/3*3+(j-1)/3]|=(1<<k);//更新状态 
}
void Take(int i,int j,int k)//将k从第i行第j列中清除，用于回溯 
{
    row[i]&=~(1<<k),col[j]&=~(1<<k),matrix[(i-1)/3*3+(j-1)/3]&=~(1<<k);//更新状态 
}
void dfs(int cnt)//搜索代码，cnt表示已填的个数 
{
    if(cnt>=N*N)//填满了 
    {
        ans++;//方案+1 
        return;
    }
    int minn=888,mx=-1,my=-1;//(mx,my)表示可填数字最少的点 
    int state=0;//这个点可填的数的状态 
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
        {
            if(vis[i][j]!=0) continue;//已经填过 
            if(isalpha(mp[i][j])&&mp[i][j]!='e'&&mp[i][j]!='o'&&ch[mp[i][j]])//这个点是一个字母 
            {
                if(!((row[i]>>ch[mp[i][j]])&1)&&!((col[j]>>ch[mp[i][j]])&1)&&!((matrix[(i-1)/3*3+(j-1)/3]>>ch[mp[i][j]])&1))
				//如果这个点可以填这个字母对应的数 
                    vis[i][j]=ch[mp[i][j]],Put(i,j,ch[mp[i][j]]),dfs(cnt+1),Take(i,j,ch[mp[i][j]]),vis[i][j]=0;//填上去 
                //剪枝2 
				return;
            }
            int can=0,x=0,s=0;
            //can表示这个点可填的数的个数 
			//x表示可填的数（用于只能填一个数的情况）
			//s表示这个点可填的数的状态
            for(int k=1;k<=N;k++)
                if(!((row[i]>>k)&1)&&!((col[j]>>k)&1)&&!((matrix[(i-1)/3*3+(j-1)/3]>>k)&1))//可以填 
                {
                    if(mp[i][j]=='e'&&!(k&1)) //判断偶数的情况 
                    can++,x=k,s+=1<<k;
                    else if(mp[i][j]=='o'&&k&1) //判断奇数的情况 
                    can++,x=k,s+=1<<k;
                    else if(mp[i][j]=='0'||(isalpha(mp[i][j])&&mp[i][j]!='e'&&mp[i][j]!='o'))//其他情况 
                    can++,x=k,s+=1<<k;
                }
            if(can==1)//只能填一个数（剪枝1） 
            {
                if(isalpha(mp[i][j])&&mp[i][j]!='e'&&mp[i][j]!='o')//如果这个格子是一个字母 
                    ch[mp[i][j]]=x;
                vis[i][j]=x;//标记为走过 
                Put(i,j,x);//更新 
                dfs(cnt+1);//继续搜索 
                Take(i,j,x);//回溯 
                vis[i][j]=0;
                ch[mp[i][j]]=0;//这里也要回溯 
                return;
            }
            if(!can) return;//若这个点一个也不能填，直接结束 
            if(can&&can<minn) minn=can,mx=i,my=j,state=s;//选取最小值 
        }
    for(int i=1;i<=N;i++)
        if((state>>i)&1)//这个数可以填 
        {
            if(isalpha(mp[mx][my])&&mp[mx][my]!='e'&&mp[mx][my]!='o')//判断字母的情况 
                ch[mp[mx][my]]=i;
            vis[mx][my]=i;//标记为走过 
            Put(mx,my,i);//更新 
            dfs(cnt+1);//继续搜索 
            Take(mx,my,i);//回溯 
            vis[mx][my]=0;
            if(isalpha(mp[mx][my])&&mp[mx][my]!='e'&&mp[mx][my]!='o')
                ch[mp[mx][my]]=0;
        } 
}
int main()
{
    int T;//多组数据 
    for(cin>>T;T--;)
    {
        memset(ch,0,sizeof(ch));
        memset(vis,0,sizeof(vis));
        memset(row,0,sizeof(row));
        memset(col,0,sizeof(col));
        memset(matrix,0,sizeof(matrix));//初始化 
        ans=0;
        int cnt=0;//已填的个数 
        for(int i=1;i<=N;i++)
            for(int j=1;j<=N;j++)
            {
                cin>>mp[i][j];
                if(mp[i][j]>='1'&&mp[i][j]<='9')//先将题目给出的数填好 
                {
                    int k=mp[i][j]-'0';
                    vis[i][j]=k;
                    Put(i,j,k);
                    cnt++;//已填的数+1 
                }
            }
        dfs(cnt);//搜索 
        cout<<ans<<"\n";//输出 
    }
    return 0;
} 
```


---

## 作者：ygsldr (赞：0)

感觉普通的暴力dfs会tle，就手打了个DLX(dancing lines algorithm X)

想说几点东西：

1.DLX建议当作模版来使用就好了

2.DLX提供的剪枝估算复杂度时可以记为原复杂度的1/10，但这个比较粗略

3.DLX 是 DL（dancing lines）和 algorithm X,其中DL是一种支持快速删除行列的数据结构，X则是精确覆盖算法

4.在DLX中，一行代表一个决策，列表示一个目标

参考程序：

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int maxcol = 1000;
const int maxnode = 10000;

int CODE[9][9][9];
//0表示 i,j要放一个数，1表示第i行要放j，2表示第i列要放j，3表示这个group要放j 
//代表了四个目标 
//也可以表示i,j上放k
 
const int Gro[9][9] = {
	{0,0,0,1,1,1,2,2,2},
	{0,0,0,1,1,1,2,2,2},
	{0,0,0,1,1,1,2,2,2},
	{3,3,3,4,4,4,5,5,5},
	{3,3,3,4,4,4,5,5,5},
	{3,3,3,4,4,4,5,5,5},
	{6,6,6,7,7,7,8,8,8},
	{6,6,6,7,7,7,8,8,8},
	{6,6,6,7,7,7,8,8,8}
};//常量数组 

struct DLX
{
	int S[maxcol];//记录这一列有几个决策可以解决 
	int U[maxnode],D[maxnode],L[maxnode],R[maxnode];//四个方向的链表 
	int col[maxnode],Row[maxnode];
	int num,ans;
	void init()
	{
		ans = 0;
		memset(S,0,sizeof(S));
		num = 324;
		for(int i(0);i <= num;++i)
		{
			U[i] = D[i] = i;
			L[i] = i - 1;
			R[i] = i + 1;
		}
		L[0] = num;
		R[num] = 0;
	}//初始化目标 
	void read()
	{
		char board[10][10];
		vector <pair<int,int> > same[26];
		for(int i(0);i < 9;++i)cin >> board[i];
		vector <int> row;row.reserve(10);
		for(int i(0);i < 9;++i)
		{
			for(int j(0);j < 9;++j)
			{
				if(board[i][j] == 'e')
				{
					for(int k(1);k < 9;k += 2)
					{
						row.clear();
						row.push_back(CODE[0][i][j]);
						row.push_back(CODE[1][i][k]);
						row.push_back(CODE[2][j][k]);
						row.push_back(CODE[3][Gro[i][j]][k]);
						add_row(CODE[i][j][k],row.begin(),row.end());
					}
				}//偶数，因为从0开始标号所以k从1开始 
				else if(board[i][j] == 'o')
				{
					for(int k(0);k < 9;k += 2)
					{
						row.clear();
						row.push_back(CODE[0][i][j]);
						row.push_back(CODE[1][i][k]);
						row.push_back(CODE[2][j][k]);
						row.push_back(CODE[3][Gro[i][j]][k]);
						add_row(CODE[i][j][k],row.begin(),row.end());
					}
				}//奇数 
				else if(board[i][j] >= 'a' && board[i][j] <= 'z')
				{
					same[board[i][j] - 'a'].push_back(make_pair(i,j));
				}//字母塞到vector里再处理 
				else if(board[i][j] == '0')
				{
					for(int k(0);k < 9;++k)
					{
						row.clear();
						row.push_back(CODE[0][i][j]);
						row.push_back(CODE[1][i][k]);
						row.push_back(CODE[2][j][k]);
						row.push_back(CODE[3][Gro[i][j]][k]);
						add_row(CODE[i][j][k],row.begin(),row.end());
					}
				}//9个数字都可以填 
				else 
				{
					int k = board[i][j] - '0' - 1;
					row.clear();
					row.push_back(CODE[0][i][j]);
					row.push_back(CODE[1][i][k]);
					row.push_back(CODE[2][j][k]);
					row.push_back(CODE[3][Gro[i][j]][k]);
					add_row(CODE[i][j][k],row.begin(),row.end());
				}//只能填一个数字 
			}
		}
		for(int alpha(0);alpha < 26;++alpha)
		{
			if(!same[alpha].empty())
			{
				for(int k(0);k < 9;++k)
				{
					row.clear();
					for(vector <pair<int,int> >::iterator itr(same[alpha].begin());itr != same[alpha].end();++itr)
					{
						int i = itr->first,j = itr->second;
						row.push_back(CODE[0][i][j]);
						row.push_back(CODE[1][i][k]);
						row.push_back(CODE[2][j][k]);
						row.push_back(CODE[3][Gro[i][j]][k]);
					}
					add_row(CODE[same[alpha][0].first][same[alpha][0].second][k],row.begin(),row.end());
				}
			}
		}//处理相同字母的情况 
	}
	void add_row(int r,vector <int>::iterator sta,vector <int>::iterator end)
	{
		int first = num + 1;
		for(vector<int>::iterator itr(sta);itr != end;++itr)
		{
			++num; ++S[*itr];
			Row[num] = r; col[num] = *itr;
			U[num] = U[*itr]; D[num] = *itr;
			D[U[num]] = num; U[D[num]] = num;
			L[num] = num - 1; R[num] = num + 1;
		}//加入一种决策，建立链表 
		L[first] = num;
		R[num] = first;
	}
	void del(int c)
	{
		R[L[c]] = R[c];
        L[R[c]] = L[c];
        for (int i = D[c]; i != c; i = D[i])
        {
            for (int j = R[i]; j != i; j = R[j])
            {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[col[j]];
            }
        }
	}//删除某个已经达成的目标 
	void remove(int c)
	{
		for (int i = U[c]; i != c; i = U[i])
        {
            for (int j = L[i]; j != i; j = L[j])
            {
                U[D[j]] = j;
                D[U[j]] = j;
                ++S[col[j]];
            }
        }
        R[L[c]] = c;
        L[R[c]] = c;
	}//回溯 
	void dfs()
	{
		if (R[0] == 0)
        {
            ++ans;//如果右边没有目标，说明搜索完成 
            return;
        }
        
        for (int i = R[0]; i != 0; i = R[i])
        {
            if (S[i] <= 0)return;
        }//没有决策可以解决，回溯 
       
        int minn = R[0];
        for (int i = R[0]; i != 0; i = R[i])
        {
            if (S[i] < S[minn])minn = i;
        }//选一个目标，使能解决他的决策最少 
        del(minn);//删除这个目标 
        for (int i = D[minn]; i != minn; i = D[i])
        {
            for (int j = R[i]; j != i; j = R[j])del(col[j]);//删除i这个决策能解决的所有目标 
            dfs();
            for (int j = L[i]; j != i; j = L[j])remove(col[j]);//回溯 
        }
        remove(minn);
	}//搜索 
};

void init()
{
	for(int k(0);k < 9;++k)
	{
		for(int i(0);i < 9;++i)
		{
			for(int j(0);j < 9;++j)
			{
				CODE[k][i][j] = 81 * k + 9 * i + j + 1;
			}
		}
	}//编码初始化 
}
DLX solver;
int main()
{
	init();
	int T;
	scanf("%d",&T);
	while(T--)
	{
		solver.init();
		solver.read();
		solver.dfs();
		printf("%d\n",solver.ans);	
	}
	return 0;
}


```

建议手动模拟一下del和remove，体验一下DL这个数据结构的作用




---

