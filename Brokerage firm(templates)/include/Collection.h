template<class... Infos>
class Collection : public Infos... // наследуем базовые классы, они же
{
    public:
        Collection(const Infos&&... infos) : Infos(infos)... {} //
};
