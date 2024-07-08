#include "Creature.h"

void Creature::OnAttacked(Creature* creature)
{
	int damage = creature->m_attack - m_defence;
	if (damage < 0)
		damage = 0;

	m_hp -= damage;
	if (m_hp < 0)
		m_hp = 0;
}