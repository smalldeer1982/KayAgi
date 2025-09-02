#include <bits/stdc++.h>
    #define vc vector
    #define INF ((int)(1e9))
    #define LINF ((ll)(1e18))
    #define pb push_back
    #define mp make_pair
    #define ll long long
    #define _tp template
    #define _tyn typename
    #define sint short int
    #define ull unsigned ll
    #define pii pair<int,int>
    #define uint unsigned int
    #define ms(_data) memset(_data,0,sizeof(_data))
    #define fin(_filename) freopen(_filename,"r",stdin)
    #define fout(_filename) freopen(_filename,"w",stdout)
    #define msn(_data,_num) memset(_data,_num,sizeof(_data))
    using namespace std;
    _tp<_tyn T>void mymax( T &_a , T _b ){ if( _a < _b ) _a = _b; }
    _tp<_tyn T>void mymin( T &_a , T _b ){ if( _a > _b ) _a = _b; }
    void print(int _x){printf("%d\n",_x);}
    void print(ll _x){printf("%I64d ",_x);}
    #define il inline
    il int in(){
        char c = getchar();
        int ret = 0;
        while( c < '0'  ||  c > '9' ) c = getchar();
        while( c >= '0'  &&  c <= '9' ){
            ret *= 10;
            ret += c-'0';
            c = getchar();
        }
        return ret;
    }
    il void read( int &x ){
        x = in();
    }
    il void read( int &x, int &y ){
        x = in(); y = in();
    }
    il void read( int &x1 , int &x2 , int &x3 ){
        x1 = in(); x2 = in(); x3 = in();
    }
    il void read( int &x1 , int &x2 , int &x3 , int &x4 ){
        x1 = in(); x2 = in(); x3 = in(); x4 = in();
    }
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    #define MAXN 110
    struct Edge{
        int to,cap,rev;
        Edge(){}
        Edge( int tt , int cc , int rr ){
            to = tt;
            cap = cc;
            rev = rr;
        }
    };
    int n,m,s,t;
    vc<Edge> e[MAXN<<1];
    vc<Edge> inp[MAXN<<1];
    il void addedge( int f , int t , int c ){
        inp[f].pb( Edge(t,c,inp[t].size()) );
        inp[t].pb( Edge(f,0,inp[f].size()-1) );
        e[f].pb(Edge());
        e[t].pb(Edge());
    }
    il void f5(){
        for( int i = 1 ; i <= n+n+1 ; i++ )
            for( uint j = 0 ; j < inp[i].size() ; j++ )
                e[i][j] = inp[i][j];
    }
    int lev[MAXN<<1];    //Level
    il void bfs( int st ){
        ms(lev);
        queue<int> q;
        q.push(st);
        lev[st] = 1;
        while( !q.empty() ){
            int now = q.front();
            q.pop();
            for( uint i = 0 ; i < e[now].size() ; i++ ){
                if( e[now][i].cap <= 0 ) continue;
                int v = e[now][i].to;
                if( !lev[v] ){
                    lev[v] = lev[now]+1;
                    q.push(v);
                }
            }
        }
    }
    bool vis[MAXN<<1];
    il int dfs( int pos , int flow ){
        if( pos == t ) return flow;
        for( uint i = 0 ; i < e[pos].size() ; i++ ){
            Edge x = e[pos][i];
            int u = x.to;
            if( vis[u] ) continue;
            if( x.cap <= 0 ) continue;
            if( lev[u] != lev[pos]+1 ) continue;
            vis[u] = 1;
            int tans = dfs( u , min(flow,x.cap) );
            vis[u] = 0;
            if( tans > 0 ){
                e[pos][i].cap -= tans;
                e[u][x.rev].cap += tans;
                return tans;
            }
        }
        return 0;
    }
    int ans = 0;
    int main(){
        read(n,m,s,t);
        for( int i = 1 ; i <= n ; i++ ){
            addedge(i,n+i,1);
        }
        for( int i = 1 ; i <= m ; i++ ){
            int a,b;
            read(a,b);
            addedge(a+n,b,INF);
            addedge(b+n,a,INF);
        }
        f5();
        while(1){
            bfs(s+n);
            if( !lev[t] ) break;
            ms(vis);
            int tans;
            while( ( tans = dfs(s+n,INF) ) > 0 ){
                ans += tans;
                ms(vis);
            }
            //cout << "[Tans] " << tans << endl;
        }
        printf("%d\n",ans);
        return 0;
    }