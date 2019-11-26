#ifndef FOOTEST_H
#define FOOTEST_H

#define W (6.88f)
#define H (6.88f)

#include "json.h"
#include <iostream>
#include <fstream>
#include <unordered_map>

//auxiliar
void vec_to_map(std::unordered_map<std::string, float>& map, b2Vec2* vertex) {
  for (int i = 0; i < 3; i++) {
    map.emplace("x" + std::to_string(i), vertex[i].x);
    map.emplace("y" + std::to_string(i), vertex[i].y);
  }
}

class FooTest : public Test {
public:
  FooTest() {
  m_world->SetGravity(b2Vec2(0,0));
  b2BodyDef def;
  def.type = b2_staticBody;
  def.position.Set(0,0);
  b2Body* m_body = m_world->CreateBody(&def);
  b2PolygonShape track;
  b2FixtureDef fixture;
  fixture.isSensor = true;
  fixture.shape = &track;

  JSON all_track;
  JSON straight;
  JSON curved;
  JSON curved_center;

  /*---------------------TRACK---------------------*/

  //right wall down
  float start1 = H;
  float end1 = W * 6; // n * W, n = tiles +1
  float center1 = 0;
  for (float i = start1; i < end1 ; i+= W) {
    track.SetAsBox( H/2, W/2, b2Vec2(center1, i), 0);
    m_body->CreateFixture(&fixture);
    std::unordered_map<std::string, float> pos;
    pos.emplace("x", center1);
    pos.emplace("y", i);
    pos.emplace("angle", 90);
    straight.emplace_back(JSON(pos));
  }

  //middle
  float start2 = H;
  float pos2 = 5 * W + W; //n * W, n = tiles + 1
  for (float i = start2; i < (start2 + 4 * W); i+= W) {
    track.SetAsBox(W/2, H/2, b2Vec2(i, pos2), 0);
    m_body->CreateFixture(&fixture);
    std::unordered_map<std::string, float> pos;
    pos.emplace("x", i);
    pos.emplace("y", pos2);
    pos.emplace("angle", 0);
    straight.emplace_back(JSON(pos));
  }

  //right wall top
  float start3 = W * 6 + H;
  float center3 = W * 5;
  float stop3 = W * 15 + H / 2;
  for (float i = start3; i < stop3; i+= W) {
    track.SetAsBox( H/2, W/2, b2Vec2(center3, i), 0);
    m_body->CreateFixture(&fixture);
    std::unordered_map<std::string, float> pos;
    pos.emplace("x", center3);
    pos.emplace("y", i);
    pos.emplace("angle", 90);
    straight.emplace_back(JSON(pos));
  }

  //ceiling
  float start4 = 5 * W ;
  float center4 = 15 * W + H; // n * W, n = tiles height
  for (float i = -start4; i < start4 ; i+= W) {
    track.SetAsBox(W/2, H/2, b2Vec2(i, center4), 0);
    m_body->CreateFixture(&fixture);
    std::unordered_map<std::string, float> pos;
    pos.emplace("x", i);
    pos.emplace("y", center4);
    pos.emplace("angle", 0);
    straight.emplace_back(JSON(pos));
  }

  //left wall
  float start5 = H;
  float stop5 = W * 15 + H / 2; //n * W, n = tiles height
  float center5 = - 5 * W - W;
  for (float i = start5; i < stop5 ; i+= W) {
    track.SetAsBox( H/2, W/2, b2Vec2(center5, i), 0);
    m_body->CreateFixture(&fixture);
    std::unordered_map<std::string, float> pos;
    pos.emplace("x", center5);
    pos.emplace("y", i);
    pos.emplace("angle", 90);
    straight.emplace_back(JSON(pos));
  }

  //ground
  float start6 = 5 * W; // n * W, n = tiles
  float end6 = 0;
  for (float i = -start6; i < end6 ; i+= W) {
    track.SetAsBox(W/2, H/2, b2Vec2(i, 0), 0);
    m_body->CreateFixture(&fixture);
    std::unordered_map<std::string, float> pos;
    pos.emplace("x", i);
    pos.emplace("y", 0);
    pos.emplace("angle", 0);
    straight.emplace_back(JSON(pos));
  }

  /*---------------------EDGES---------------------*/

  int32 count = 3;

  //down right edge
  b2Vec2 vertices1[3];
  vertices1[0].Set( - W / 2, W / 2);
  vertices1[1].Set(W / 2, W /2);
  vertices1[2].Set(-W /2, -W / 2);
  b2PolygonShape edge1;
  edge1.Set(vertices1, count);
  std::unordered_map<std::string, float> vertex_edge1;
  vec_to_map(vertex_edge1, edge1.m_vertices);
  curved.emplace_back(JSON(vertex_edge1));
  b2FixtureDef fixture_edge1;
  fixture_edge1.shape = &edge1;
  fixture_edge1.isSensor = true;
  m_body->CreateFixture(&fixture_edge1);
  std::unordered_map<std::string, float> pos_edge1;
  pos_edge1.emplace("x", 0);
  pos_edge1.emplace("y", 0);
  pos_edge1.emplace("angle", 270);
  curved_center.emplace_back(JSON(pos_edge1));

  //middle left edge
  b2Vec2 vertices2[3];
  float edge2_x1 = W / 2;
  float edge2_x2 = - W / 2;
  float edge2_y1 = (W/2) + (5 * W);
  float edge2_y2 = edge2_y1 + W;
  vertices2[0].Set(edge2_x1, edge2_y1);
  vertices2[1].Set(edge2_x1, edge2_y2);
  vertices2[2].Set(edge2_x2, edge2_y1);
  b2PolygonShape edge2;
  edge2.Set(vertices2, count);
  std::unordered_map<std::string, float> vertex_edge2;
  vec_to_map(vertex_edge2, edge2.m_vertices);
  curved.emplace_back(JSON(vertex_edge2));
  b2FixtureDef fixture_edge2;
  fixture_edge2.shape = &edge2;
  fixture_edge2.isSensor = true;
  m_body->CreateFixture(&fixture_edge2);
  std::unordered_map<std::string, float> pos_edge2;
  pos_edge2.emplace("x", 0);
  pos_edge2.emplace("y", 6 * W);
  pos_edge2.emplace("angle", 90);
  curved_center.emplace_back(JSON(pos_edge2));

  //middle right edge
  b2Vec2 vertices3[3];
  float edge3_x1 = W / 2 + 4 * W;
  float edge3_x2 = edge3_x1 + W;
  float edge3_y1 = (W/2) + (5 * W);
  float edge3_y2 = edge3_y1 + W;
  vertices3[0].Set(edge3_x1, edge3_y1);
  vertices3[1].Set(edge3_x1, edge3_y2);
  vertices3[2].Set(edge3_x2, edge3_y2);
  b2PolygonShape edge3;
  edge3.Set(vertices3, count);
  std::unordered_map<std::string, float> vertex_edge3;
  vec_to_map(vertex_edge3, edge3.m_vertices);
  curved.emplace_back(JSON(vertex_edge3));
  b2FixtureDef fixture_edge3;
  fixture_edge3.shape = &edge3;
  fixture_edge3.isSensor = true;
  m_body->CreateFixture(&fixture_edge3);
  std::unordered_map<std::string, float> pos_edge3;
  pos_edge3.emplace("x", 5 * W);
  pos_edge3.emplace("y", 6 * W);
  pos_edge3.emplace("angle", 270);
  curved_center.emplace_back(JSON(pos_edge3));

  //top right edge
  b2Vec2 vertices4[3];
  float edge4_x1 = (W/2) + (4 * W);;
  float edge4_x2 = edge4_x1 + W;
  float edge4_y1 = (W/2) + (15 * W);
  float edge4_y2 = edge4_y1 + W;
  vertices4[0].Set(edge4_x1, edge4_y1);
  vertices4[1].Set(edge4_x1, edge4_y2);
  vertices4[2].Set(edge4_x2, edge4_y1);
  b2PolygonShape edge4;
  edge4.Set(vertices4, count);
  std::unordered_map<std::string, float> vertex_edge4;
  vec_to_map(vertex_edge4, edge4.m_vertices);
  curved.emplace_back(JSON(vertex_edge4));
  b2FixtureDef fixture_edge4;
  fixture_edge4.shape = &edge4;
  fixture_edge4.isSensor = true;
  m_body->CreateFixture(&fixture_edge4);
  std::unordered_map<std::string, float> pos_edge4;
  pos_edge4.emplace("x", 5 * W);
  pos_edge4.emplace("y", 16 * W);
  pos_edge4.emplace("angle", 180);
  curved_center.emplace_back(JSON(pos_edge4));

  //top left edge
  b2Vec2 vertices5[3];
  float edge5_x1 = 5 * W + W / 2;
  float edge5_x2 = 5 * W + W / 2 + W;
  float edge5_y1 = (W/2) + (15 * W);
  float edge5_y2 = edge5_y1 + W;
  vertices5[0].Set(-edge5_x1, edge5_y1);
  vertices5[1].Set(-edge5_x1, edge5_y2);
  vertices5[2].Set(-edge5_x2, edge5_y1);
  b2PolygonShape edge5;
  edge5.Set(vertices5, count);
  std::unordered_map<std::string, float> vertex_edge5;
  vec_to_map(vertex_edge5, edge5.m_vertices);
  curved.emplace_back(JSON(vertex_edge5));
  b2FixtureDef fixture_edge5;
  fixture_edge5.shape = &edge5;
  fixture_edge5.isSensor = true;
  m_body->CreateFixture(&fixture_edge5);
  std::unordered_map<std::string, float> pos_edge5;
  pos_edge5.emplace("x", - 6 * W);
  pos_edge5.emplace("y", 16 * W);
  pos_edge5.emplace("angle", 90);
  curved_center.emplace_back(JSON(pos_edge5));

  //down left edge
  b2Vec2 vertices6[3];
  float edge6_x1 = 5 * W + W / 2;
  float edge6_x2 = edge6_x1 + W;
  vertices6[0].Set(-edge6_x1, W / 2);
  vertices6[1].Set(-edge6_x1, -W / 2);
  vertices6[2].Set(-edge6_x2, W / 2);
  b2PolygonShape edge6;
  edge6.Set(vertices6, count);
  std::unordered_map<std::string, float> vertex_edge6;
  vec_to_map(vertex_edge6, edge6.m_vertices);
  curved.emplace_back(JSON(vertex_edge6));
  b2FixtureDef fixture_edge6;
  fixture_edge6.shape = &edge6;
  fixture_edge6.isSensor = true;
  m_body->CreateFixture(&fixture_edge6);
  std::unordered_map<std::string, float> pos_edge6;
  pos_edge6.emplace("x", - 6 * W);
  pos_edge6.emplace("y", 0);
  pos_edge6.emplace("angle", 0);
  curved_center.emplace_back(JSON(pos_edge6));

/*--------------------LIMIT------------------------*/

  //create box
  b2BodyDef def_box;
  def_box.type = b2_staticBody;
  def_box.position.Set(0,0);
  b2Body* box_body = m_world->CreateBody(&def_box);
  b2PolygonShape limit_box;
  b2FixtureDef fixture_box_def;
  fixture_box_def.shape = &limit_box;
  limit_box.SetAsBox( 50, 1, b2Vec2(0, -10), 0);//ground
  box_body->CreateFixture(&fixture_box_def);
  limit_box.SetAsBox( 50, 1, b2Vec2(0, 120), 0);//ceiling
  box_body->CreateFixture(&fixture_box_def);
  limit_box.SetAsBox( 1, 65, b2Vec2(-50,55), 0);//left wall
  box_body->CreateFixture(&fixture_box_def);
  limit_box.SetAsBox( 1, 65, b2Vec2(50, 55), 0);//right wall
  box_body->CreateFixture(&fixture_box_def);

  all_track["straight"] = straight;
  all_track["curved_center"] = curved_center;
  all_track["curved"] = curved;
  std::ofstream file;
  file.open("track.txt");
  file<<all_track.dump();
  file.close();
  }

  void Step(Settings* settings) {
    //run the default physics and rendering
    Test::Step(settings);

    //show some text in the main screen
    g_debugDraw.DrawString(5, m_textLine, "Track");
    m_textLine += 15;
  }

  static Test* Create() {
    return new FooTest;
  }
};

#endif
