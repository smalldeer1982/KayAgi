# Item World

## 题目描述

你有 $n$ 个物品，每个物品都有攻击力 $atk$，防御力 $def$，魔法值 $res$。

每件物品都属于以下三种之一：武器 $\text{weapon}$，防具 $\text{armor}$ 和宝具 $\text{orb}$。

现在有 $m$ 个居民住在物品中，每个居民都会给所居住的物品提供加成。

每个居民都属于以下三种之一：斗士 $\text{gladiator}$，侍卫 $\text{sentry}$ 和法师 $\text{physician}$。

其中，斗士可以增加物品的 $atk$ 值，侍卫可以增加物品的 $def$ 值，法师可以增加物品的 $res$ 值。

每个物品都有一个容量，表示能生存在这个物品内的最大居民数量，我们可以让居民在不同物品中跑来跑去。在一个时刻内我们可以在一件物品中取出若干个居民，并分散至若干个别的容量还没满的物品中。我们不可以把居民扔到物品外面，在任意时刻中居民都需要生存在物品中。

Laharl 有一些物品。他想在挪动一些居民后装备上一件武器、一件防具和一件宝具。在 Laharl 挪动居民后，应该使他装备的武器的 $atk$ 值最大。在满足以上条件的前提下，要尽量使他装备的防具的 $def$ 值最大。在满足以上两个条件的前提下，要尽量使他装备的宝具的 $res$ 值最大。

请你找到最佳的装备方案。

## 样例 #1

### 输入

```
4
sword weapon 10 2 3 2
pagstarmor armor 0 15 3 1
iceorb orb 3 2 13 2
longbow weapon 9 1 2 1
5
mike gladiator 5 longbow
bobby sentry 6 pagstarmor
petr gladiator 7 iceorb
teddy physician 6 sword
blackjack sentry 8 sword
```

### 输出

```
sword 2 petr mike 
pagstarmor 1 blackjack 
iceorb 2 teddy bobby 
```

## 样例 #2

### 输入

```
4
sword weapon 10 2 3 2
pagstarmor armor 0 15 3 1
iceorb orb 3 2 13 2
longbow weapon 9 1 2 1
6
mike gladiator 5 longbow
bobby sentry 6 pagstarmor
petr gladiator 7 iceorb
teddy physician 6 sword
blackjack sentry 8 sword
joe physician 6 iceorb
```

### 输出

```
longbow 1 mike 
pagstarmor 1 bobby 
iceorb 2 petr joe 
```

# 题解

## 作者：LiQXing (赞：1)

蛮有意思的模拟题。

题意十分混乱，一会儿出现 $gladiator$，一会儿出现 $weapon$。

不如把它们归类，把与 $atk$ 有关的统称为 $atk$，把与 $def$ 有关的统称为 $def$，把与 $res$ 有关的统称为 $res$。

注意，题目中提到居民不可以出现在外面，所以如果居民人数等于所有物品的总容量，那就不可以交换居民的位置。反之，只要有一个空缺的位置，那么就可以任意分配居民的位置。

当没有空缺的时候，我们只用枚举最多的物品就行了。

如果有空缺，贪心的寻找那种物品可以达到最大的价值。

然后还有一个坑点，最后的情况一定是能够容纳所有居民的，所以我们如果一个物品的容量还有多的，就可以把一个无关的居民加入到这个物品中，这样一定更优。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define i64 long long
#define ull unsigned long long
#define ldb long double
#define db double
#define i128 __int128
#define up(a,b,c) for(int a=b;a<=c;a++)
#define dn(a,b,c) for(int a=b;a>=c;a--)
#define pii pair<int,int>
#define lc k<<1
#define rc k<<1|1
#define fi first
#define se second
#define endl '\n'

const int N=2e5+100,M=1e6+100;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;
const ull uinf=1e18+14;

int n,m;
struct node{
    string name,type;
    int atk,def,res,siz;
}a[N];
struct people{
    string name,type;
    int bonus;
    string home;
}p[N];
int sumsiz;
bool vis[N];
signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    up(i,1,n){
        cin>>a[i].name>>a[i].type>>a[i].atk>>a[i].def>>a[i].res>>a[i].siz;
        if(a[i].type=="weapon")a[i].type="atk";
        else if(a[i].type=="armor")a[i].type="def";
        else if(a[i].type=="orb")a[i].type="res";
        sumsiz+=a[i].siz;
    }
    cin>>m;
    up(i,1,m){
        cin>>p[i].name>>p[i].type>>p[i].bonus>>p[i].home;
        if(p[i].type=="gladiator")p[i].type="atk";
        else if(p[i].type=="sentry")p[i].type="def";
        else if(p[i].type=="physician")p[i].type="res";
    }
    if(sumsiz==m){
        int posatk=0,posdef=0,posres=0,maxatk=-inf,maxdef=-inf,maxres=-inf;
        up(i,1,n){
            if(a[i].type=="atk"){
                int atk=a[i].atk;
                up(j,1,m)if(p[j].home==a[i].name&&p[j].type=="atk")atk+=p[j].bonus;
                if(atk>maxatk){
                    posatk=i;
                    maxatk=atk;
                }
            }
            if(a[i].type=="def"){
                int def=a[i].def;
                up(j,1,m)if(p[j].home==a[i].name&&p[j].type=="def")def+=p[j].bonus;                
                if(def>maxdef){
                    posdef=i;
                    maxdef=def;
                }
            }
            if(a[i].type=="res"){
                int res=a[i].res;
                up(j,1,m)if(p[j].home==a[i].name&&p[j].type=="res")res+=p[j].bonus;
                if(res>maxres){
                    posres=i;
                    maxres=res;
                }
            }
        }
        int numatk=0,numres=0,numdef=0;
        up(j,1,m)if(p[j].home==a[posatk].name)numatk++;
        cout<<a[posatk].name<<" "<<numatk<<" ";
        up(j,1,m)if(p[j].home==a[posatk].name)cout<<p[j].name<<" ";cout<<endl;
        up(j,1,m)if(p[j].home==a[posdef].name)numdef++;
        cout<<a[posdef].name<<" "<<numdef<<" ";
        up(j,1,m)if(p[j].home==a[posdef].name)cout<<p[j].name<<" ";cout<<endl;
        up(j,1,m)if(p[j].home==a[posres].name)numres++;
        cout<<a[posres].name<<" "<<numres<<" ";
        up(j,1,m)if(p[j].home==a[posres].name)cout<<p[j].name<<" ";cout<<endl;
        return 0;
    } 
    vector<pii>atk,def,res;
    up(i,1,m){
        if(p[i].type=="atk")atk.push_back({p[i].bonus,i});
        if(p[i].type=="def")def.push_back({p[i].bonus,i});
        if(p[i].type=="res")res.push_back({p[i].bonus,i});
    }
    sort(atk.rbegin(),atk.rend());
    sort(def.rbegin(),def.rend());
    sort(res.rbegin(),res.rend());
    int posatk=0,posdef=0,posres=0,maxatk=-inf,maxdef=-inf,maxres=-inf;
    up(i,1,n){
        if(a[i].type=="atk"){
            int atkw=a[i].atk;
            up(j,0,min(a[i].siz,(int)atk.size())-1)atkw+=atk[j].first;
            if(atkw>maxatk){
                posatk=i;
                maxatk=atkw;
            }
        }
        if(a[i].type=="def"){
            int defw=a[i].def;
            up(j,0,min(a[i].siz,(int)def.size())-1)defw+=def[j].first;     
            if(defw>maxdef){
                posdef=i;
                maxdef=defw;
            }
        }
        if(a[i].type=="res"){
            int resw=a[i].res;
            up(j,0,min(a[i].siz,(int)res.size())-1)resw+=res[j].first;
            if(resw>maxres){
                posres=i;
                maxres=resw;
            }
        }
    }
    vector<int>atkpos,defpos,respos;
    up(i,0,min(a[posatk].siz,(int)atk.size())-1)atkpos.push_back(atk[i].second),vis[atk[i].second]=1;
    up(i,0,min(a[posdef].siz,(int)def.size())-1)defpos.push_back(def[i].second),vis[def[i].second]=1;
    up(i,0,min(a[posres].siz,(int)res.size())-1)respos.push_back(res[i].second),vis[res[i].second]=1;
    up(i,1,m){
        if(vis[i])continue;
        if(atkpos.size()<a[posatk].siz)atkpos.push_back(i),vis[i]=1;;
    }
    cout<<a[posatk].name<<" "<<atkpos.size()<<" ";
    for(auto v:atkpos)cout<<p[v].name<<" ";cout<<endl;
    up(i,1,m){
        if(vis[i])continue;
        if(defpos.size()<a[posdef].siz)defpos.push_back(i),vis[i]=1;;
    }
    cout<<a[posdef].name<<" "<<defpos.size()<<" ";
    for(auto v:defpos)cout<<p[v].name<<" ";cout<<endl;
    up(i,1,m){
        if(vis[i])continue;
        if(respos.size()<a[posres].siz)respos.push_back(i),vis[i]=1;;
    }
    cout<<a[posres].name<<" "<<respos.size()<<" ";
    for(auto v:respos)cout<<p[v].name<<" ";cout<<endl;
    return 0;
}
```




---

