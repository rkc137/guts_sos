#include "SceneManager.hpp"
#include "../ui/label/label.hpp"

class Opening : public SceneManager::Scene
{
public:
    void resize() override;
    void update(double delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Time duration = sf::seconds(5);
    sf::Clock clock;
    sf::Color color{255, 255, 255, 0};
    ui::Label author{L"made by rkc137", res::cybersomething, color};
    ui::Label made_with{L"made with sfml", res::cybersomething, color};
};