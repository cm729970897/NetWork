//
// Created by Administrator on 2020/3/17.
//

#ifndef EPOLL_CHANNEL_MAP_H
#define EPOLL_CHANNEL_MAP_H

// channel映射表，key为对应的socket描述字
struct channel_map
{
    void **entries;
    int nentries;
};

int map_make_space(struct channel_map *map, int slot, int msize);
void map_init(struct channel_map *map);
void map_clear(struct channel_map *map);

#endif //EPOLL_CHANNEL_MAP_H
