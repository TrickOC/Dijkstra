#include <iostream>
#include <vector>
#include <set>
#include <list>

int main() {
    int n, m, b, i, vo, vd, p;

    std::cin >> n >> m >> b >> i;
    std::vector<std::vector<std::pair<int, int>>> vertices(n, std::vector<std::pair<int, int>>());

    for (int j = 0; j < m; j++) {
        std::cin >> vo >> vd >> p;
        vertices[vo-1].emplace_back(vd-1,p);
    }

    int passos[n];
    passos[i-1] = 0;
    std::vector<int> peso(n, 1e9);
    peso[i-1] = 0;

    std::set<std::pair<int, int>> fila;
    for (int k = 0; k < n; k++)
        fila.insert({peso[k], k});

    while (!fila.empty()) {
        auto [d, vo] = *fila.begin();
        fila.erase(fila.begin());
        for (auto &[vd, p] : vertices[vo]) {
            if (peso[vo] + p >= peso[vd])
                continue;
            fila.erase(fila.find({peso[vd], vd}));
            peso[vd] = peso[vo] + p;
            fila.insert({peso[vd], vd});
            passos[vd] = vo;
        }
    }

    int v;
    std::list<int> aux;
    for (int l = 0; l < n; l++) {
        if (l == i-1) continue;
        v = l;
        std::cout << l+1 << " (" << peso[l] << "): " << i;
        while (passos[v] != i-1) {
            aux.emplace_front(passos[v]);
            v = passos[v];
        }
        for (auto passo : aux)
            std::cout << " " << passo+1;
        std::cout << " " << l+1 << std::endl;
        aux.clear();
    }

    return 0;
}