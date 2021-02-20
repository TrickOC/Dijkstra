#include <iostream>
#include <vector>
#include <set>

int main() {
    int n, m, b, i, vo, vd, p;

    std::cin >> n >> m >> b >> i;
    std::vector<std::vector<std::pair<int, int>>> vertices(n, std::vector<std::pair<int, int>>());

    for (int j = 0; j < m; j++) {
        std::cin >> vo >> vd >> p;
        vertices[vo-1].emplace_back(vd-1,p);
    }

    std::vector<int> aux(n, 1e9);
    aux[i-1] = 0;

    std::set<std::pair<int, int>> fila;
    for (int k = 0; k < n; k++)
        fila.insert({aux[k], k});

    while (!fila.empty()) {
        auto [d, vo] = *fila.begin();
        fila.erase(fila.begin());
        for (auto &[vd, p] : vertices[vo]) {
            if (aux[vo] + p >= aux[vd]) continue;
            fila.erase(fila.find({aux[vd], vd}));
            aux[vd] = aux[vo] + p;
            fila.insert({aux[vd], vd});
        }
    }

    for (int l = 0; l < n; l++) {
        if (l+1 == i) continue;
        std::cout << l+1 << " (" << aux[l] << "): " << i << std::endl;
    }

    return 0;
}