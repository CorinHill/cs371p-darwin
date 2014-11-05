/*
    int action = 0;
    while(1) {
      Line line;
      try {
        line = _sp.lines.at(_pc);
      } catch(std::out_of_range e) {
        action = -1;
      }
      if(action) break;
      switch(Line.ins) {
      case HOP   : action = 1; break;
      case LEFT  : action = 0;
        switch(_dir) {
        case NORTH: _dir = WEST; break;
        case SOUTH: _dir = EAST; break;
        case EAST : _dir = NORTH; break;
        case WEST : _dir = SOUTH; break;
        }
        break;
      case Right : action = 0;
        switch(_dir) {
        case NORTH: _dir = WEST; break;
        case SOUTH: _dir = EAST; break;
        case EAST : _dir = NORTH; break;
        case WEST : _dir = SOUTH; break;
        }
        break;
      case INFECT: action = (&other == &_sp)? 0 : 2; break;
      case IF_E  : if(ahead == EMPTY) _pc = line.target
      }
*/
