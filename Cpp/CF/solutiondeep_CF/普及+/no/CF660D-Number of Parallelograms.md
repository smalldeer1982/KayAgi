# 题目信息

# Number of Parallelograms

## 题目描述

给定平面上$n$个点，问用这些点能组成多少平行四边形（多个平行四边形可以共用点，保证任意三点不共线）

## 说明/提示

$1 \leq n \leq 2000$ , $0\leq x_i,y_i \leq 10^{9}$

## 样例 #1

### 输入

```
4
0 1
1 0
1 1
2 0
```

### 输出

```
1
```

# AI分析结果

### 题目内容
# 平行四边形的数量

## 题目描述
给定平面上$n$个点，问用这些点能组成多少平行四边形（多个平行四边形可以共用点，保证任意三点不共线）。

## 说明/提示
$1 \leq n \leq 2000$ ，$0\leq x_i,y_i \leq 10^{9}$ 。

## 样例 #1
### 输入
```
4
0 1
1 0
1 1
2 0
```
### 输出
```
1
```

### 算法分类
数学

### 综合分析与结论
这些题解主要基于平行四边形的性质来解题，大部分题解利用“对角线互相平分”这一性质，通过枚举点对计算中点并统计相同中点的数量来得出平行四边形个数；有两个题解利用“对边平行且相等”，通过枚举点对构建向量，统计相同向量的数量来求解，不过这两个题解需注意去重。各题解思路清晰，主要区别在于利用的平行四边形性质不同以及实现细节上。

### 所选的题解
- **作者：世末OIer（5星）**
  - **关键亮点**：思路清晰，代码简洁明了，直接利用平行四边形对角线互相平分性质，通过`map`统计中点出现次数，进而计算平行四边形个数。
  - **重点代码**：
```cpp
map<pair<int,int>,int>cnt;
int n,x[2002],y[2002];
int main(){
    int i,j;
    scanf("%d",&n);
    for(i=0;i<n;++i) scanf("%d%d",x+i,y+i);
    for(i=0;i<n;++i) for(j=0;j<i;++j) ++cnt[mp(x[i]+x[j],y[i]+y[j])];
    ll ans=0;
    for(map<pair<int,int>,int>::iterator it=cnt.begin();it!=cnt.end();it++){
        int t=it->second;
        ans+=t*(t-1)/2;
    }
    printf("%I64d\n",ans);
    return 0;
}
```
  - **核心实现思想**：先读入所有点坐标，然后枚举所有点对，计算中点（通过坐标和避免小数）并在`map`中计数，最后遍历`map`，根据组合数公式计算平行四边形个数。
- **作者：jianhe（4星）**
  - **关键亮点**：同样利用对角线互相平分性质，代码简洁，利用`map`统计中点，并且使用`auto`简化遍历`map`操作。
  - **重点代码**：
```cpp
const ll N=2010;
ll n,x[N],y[N],ans;
map<pair<ll,ll>,ll> p;
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            p[{x[i]+x[j],y[i]+y[j]}]++;
    for(auto t:p) ans+=t.second*(t.second-1)/2;
    cout<<ans;
    return 0;
}
```
  - **核心实现思想**：读入点坐标后，枚举点对计算中点并存入`map`，遍历`map`根据组合数计算平行四边形个数。
- **作者：xunhuanyihao（4星）**
  - **关键亮点**：对利用对角线互相平分性质解题思路阐述清晰，对时间复杂度分析到位。
  - **重点代码**：
```cpp
const int N = 1e6 + 10;
typedef long long ll;
typedef pair<int, int> pii;
int n;
pii a[N];
map<pii, int>mp;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
    }
    for (int i = 1; i <= n; i++) 
        for (int j = i + 1; j <= n; j++) { 
            mp[{a[i].first + a[j].first, a[i].second + a[j].second}]++;
        }
    ll ans = 0;
    for (auto [x, y] : mp) {
        ans += y * (y - 1) / 2;
    }
    printf("%lld\n", ans);
    return 0;
}
```
  - **核心实现思想**：读入点坐标后，枚举点对计算中点并在`map`计数，遍历`map`按组合数计算平行四边形个数。

### 最优关键思路或技巧
利用平行四边形对角线互相平分的性质，通过枚举点对计算中点坐标（为避免小数，采用坐标和的方式），使用`map`统计相同中点的数量，根据组合数公式计算平行四边形的个数。这种方法简洁高效，避免了复杂的几何计算。

### 拓展
同类型题常围绕几何图形的性质展开，类似算法套路是深入挖掘图形性质，将几何问题转化为代数问题，利用数据结构辅助统计和计算。例如对于矩形、菱形等图形，也可通过类似方式，依据其特殊性质来解决数量统计问题。

### 洛谷相似题目
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：考察组合数学相关知识。
- [P2181 对角线](https://www.luogu.com.cn/problem/P2181)：通过数学方法解决多边形对角线相关问题。
- [P1025 数的划分](https://www.luogu.com.cn/problem/P1025)：涉及整数划分的组合问题。 

---
处理用时：55.74秒