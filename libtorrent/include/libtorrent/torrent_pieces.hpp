#ifndef TORRENT_TORRENT_PIECES_HPP_INCLUDED
#define TORRENT_TORRENT_PIECES_HPP_INCLUDED

#include <vector>

#include "libtorrent/config.hpp"
#include "libtorrent/intrusive_ptr_base.hpp"
#include "libtorrent/assert.hpp"

namespace libtorrent
{
	class TORRENT_EXPORT torrent_pieces : public intrusive_ptr_base<torrent_pieces>
	{
	public:
		torrent_pieces(int block_size) : m_block_size(block_size) {};
		~torrent_pieces();

		int num_pieces() const
		{
			return int(m_piece_size.size());
		}

		int get(int index) const
		{
			TORRENT_ASSERT(index >= 0);
			TORRENT_ASSERT(index < (int)m_piece_size.size() || m_piece_size.empty());
			TORRENT_ASSERT(m_piece_size[index] > 0);
			return m_piece_size[index];
		}

		int blocks_in_piece(int index) const
		{
			TORRENT_ASSERT(index >= 0);
			TORRENT_ASSERT(index < (int)m_piece_size.size() || m_piece_size.empty());
			TORRENT_ASSERT(m_piece_size[index] > 0);
			return (m_piece_size[index] + m_block_size - 1) / m_block_size;
		}

		int blocks_in_last_piece() const
		{
			TORRENT_ASSERT(m_piece_size.back() > 0);
			return (m_piece_size.back() + m_block_size - 1) / m_block_size;
		}

		void init(int blocks_per_piece, int blocks_in_last_piece, int total_num_pieces)
		{
			m_piece_size.clear();
			m_piece_size.resize(total_num_pieces, blocks_per_piece * m_block_size);
			if( blocks_in_last_piece )
				m_piece_size.back() = blocks_in_last_piece * m_block_size;
			TORRENT_ASSERT(m_piece_size.back() <= blocks_per_piece);
		}

		void set(int piece, int size)
		{
			if( piece >= (int) m_piece_size.size() ) {
				m_piece_size.resize(piece + 1, 0);
			}
			m_piece_size[piece] = size;
		}

	private:
		int m_block_size;
		std::vector<int> m_piece_size;
	};
}

#endif // TORRENT_TORRENT_PIECES_HPP_INCLUDED

