//
// RessourceManager.hpp for Gomoku in /home/mikaz3/Tek3/B5/AI/Gomoku
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec  6 14:07:10 2016 Thomas Billot
// Last update Tue Dec  6 15:04:51 2016 Thomas Billot
//

#ifndef			_RESOURCEMANAGER_HPP_
# define		_RESOURCEMANAGER_HPP_

# include	        <unordered_map>
# include		<memory>
# include		<map>

template<typename Resource, typename Identifier>
class			ResourceManager
{

public:
  
  explicit		ResourceManager() {}
  ~ResourceManager	() {}
  
  const Resource	&load(const Identifier &id)
  {
    if (_resources[id] != NULL)
      return *(_resources[id].get());
    
    Resource *resource = new Resource;
    
    if (!resource->loadFromFile(id))
      throw std::logic_error("Error: Load resource " + id);
    std::unique_ptr<Resource>	pr(resource);
    _resources[id] = std::move(pr);
    return *(_resources[id].get());
  }

private:
  
  std::unordered_map<Identifier, std::unique_ptr<Resource> >	_resources;
  const ResourceManager &RessourceManager(const ResourceManager &lhs);
  const ResourceManager &operator=(const ResourceManager &lhs);
};

#endif			/* _RESSOURCEMANAGER_HPP_ */
